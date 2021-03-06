/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/log/default_parameters.hpp>
#include <sge/opencl/exception.hpp>
#include <sge/opencl/log_location.hpp>
#include <sge/opencl/system.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/context/parameters.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/platform/object.hpp>
#include <sge/opencl/single_device_system/object.hpp>
#include <sge/opencl/single_device_system/parameters.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/thread/locks.hpp>
#include <functional>
#include <mutex>
#include <fcppt/config/external_end.hpp>


namespace
{
sge::opencl::context::parameters
construct_context_parameters(
	sge::opencl::platform::object &_platform,
	sge::opencl::device::object &_device,
	sge::opencl::context::error_callback const &_error_callback,
	sge::opencl::single_device_system::optional_renderer const &_opt_renderer)
{
	sge::opencl::context::parameters result(
		_platform,
		sge::opencl::device::object_ref_sequence{
			fcppt::make_ref(
				_device
			)
		}
	);

	result.error_callback(
		_error_callback);

	fcppt::optional::maybe_void(
		_opt_renderer,
		[
			&result
		](
			fcppt::reference<
				sge::renderer::device::core
			> const _renderer
		)
		{
			result.share_with(
				_renderer.get()
			);
		}
	);

	return result;
}

sge::opencl::platform::object &
choose_platform(
	fcppt::log::object &_log,
	sge::opencl::platform::object_sequence &objects,
	bool const prefer_gpu)
{
	if(!prefer_gpu)
		return
			objects.front();

	for(
		auto &platform : objects)
		if(platform.has_gpu())
			return platform;

	FCPPT_LOG_WARNING(
		_log,
		fcppt::log::out
			<<
			FCPPT_TEXT("You preferred a GPU platform, but I didn't find one, so choosing a non-GPU platform now.")
	)

	return
		objects.front();
}
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::opencl::single_device_system::object::object(
	fcppt::log::context &_log_context,
	single_device_system::parameters const &_params)
:
	log_{
		_log_context,
		sge::opencl::log_location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("single_device_system::object")
			}
		)
	},
	system_(
		fcppt::make_unique_ptr<sge::opencl::system>()),
	platform_(
		&choose_platform(
			log_,
			system_->platforms(),
			_params.prefers_gpu())),
	device_(
		&platform_->devices().front()),
	context_(
		fcppt::make_unique_ptr<context::object>(
			::construct_context_parameters(
				*platform_,
				*device_,
				sge::opencl::context::error_callback{
					std::bind(
						&object::error_callback,
						this,
						std::placeholders::_1,
						std::placeholders::_2
					)
				},
				_params.renderer()
			)
		)
	),
	queue_(
		fcppt::make_unique_ptr<command_queue::object>(
			*device_,
			*context_,
			command_queue::execution_mode::in_order,
			_params.profiling())),
	error_mutex_(),
	error_occured_(
		false),
	error_information_(),
	error_data_(),
	error_callback_(
		_params.error_callback())
{
}
FCPPT_PP_POP_WARNING

void
sge::opencl::single_device_system::object::update()
{
	std::lock_guard<std::mutex> l(
		error_mutex_);

	if(!error_occured_)
		return;

	fcppt::optional::to_exception(
		error_callback_,
		[
			this
		]{
			return
				sge::opencl::exception(
					FCPPT_TEXT("An asynchronous error occured: ")+
					fcppt::from_std_string(
						error_information_
					)
				);
		}
	)(
		error_information_,
		error_data_
	);
}

sge::opencl::system &
sge::opencl::single_device_system::object::system()
{
	return *system_;
}

sge::opencl::system const &
sge::opencl::single_device_system::object::system() const
{
	return *system_;
}

sge::opencl::platform::object &
sge::opencl::single_device_system::object::platform()
{
	return *platform_;
}

sge::opencl::platform::object const &
sge::opencl::single_device_system::object::platform() const
{
	return *platform_;
}

sge::opencl::device::object &
sge::opencl::single_device_system::object::device()
{
	return *device_;
}

sge::opencl::device::object const &
sge::opencl::single_device_system::object::device() const
{
	return *device_;
}

sge::opencl::context::object &
sge::opencl::single_device_system::object::context()
{
	return *context_;
}

sge::opencl::context::object const &
sge::opencl::single_device_system::object::context() const
{
	return *context_;
}

sge::opencl::command_queue::object &
sge::opencl::single_device_system::object::command_queue()
{
	return *queue_;
}

sge::opencl::command_queue::object const &
sge::opencl::single_device_system::object::command_queue() const
{
	return *queue_;
}

sge::opencl::single_device_system::object::~object()
{
	// Consider the following scenario: An OpenCL function in thread A
	// fails. The error callback is triggered from thread B, which acquires
	// the error_mutex. At the same time, the failed function in thread A
	// triggers an exception. This causes single_device_system to be
	// destroyed. But the mutex might still be locked in thread B! So we
	// have to wait here.
	std::lock_guard<std::mutex> l(
		error_mutex_);
}

void
sge::opencl::single_device_system::object::error_callback(
	opencl::error_information_string const &_error_information,
	opencl::binary_error_data const &_error_data)
{
	std::lock_guard<std::mutex> l(
		error_mutex_);

	error_information_ =
		_error_information;

	error_data_ =
		_error_data;

	FCPPT_LOG_ERROR(
		log_,
		fcppt::log::out
			<<
			FCPPT_TEXT("An error in a context occured: \"")
			<<
			boost::algorithm::trim_copy(
				fcppt::from_std_string(
					_error_information
				)
			)
			<<
			FCPPT_TEXT("\"")
	)
}
