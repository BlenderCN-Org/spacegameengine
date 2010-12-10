/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/window/instance.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/tr1/functional.hpp>
#include <awl/window/event/processor.hpp>
#include <awl/window/instance.hpp>
#include <awl/mainloop/io_service.hpp>

sge::window::instance::instance(
	awl::system::object_ptr const _system,
	awl::window::instance_ptr const _instance,
	awl::window::event::processor_ptr const _window_processor,
	awl::mainloop::io_service_ptr const _io_service
)
:
	system_(
		_system
	),
	instance_(
		_instance
	),
	window_processor_(
		_window_processor
	),
	io_service_(
		_io_service
	),
	dispatcher_(
		io_service_
		?
			io_service_->create_dispatcher(
				system_,
				std::tr1::bind(
					&instance::dispatch,
					this
				)
			)
		:

			awl::mainloop::dispatcher_ptr()
	)
{}

sge::window::instance::~instance()
{}

sge::window::dim_type const
sge::window::instance::size() const
{
	return
		fcppt::math::dim::structure_cast<
			sge::window::dim_type
		>(
			instance_->size()
		);
}

void
sge::window::instance::show()
{
	instance_->show();
}

void
sge::window::instance::dispatch()
{
	window_processor_->dispatch();
}

awl::system::object_ptr const
sge::window::instance::awl_system() const
{
	return system_;
}

awl::window::instance_ptr const
sge::window::instance::awl_instance() const
{
	return instance_;
}

awl::window::event::processor_ptr const
sge::window::instance::awl_window_event_processor() const
{
	return window_processor_;
}

awl::mainloop::io_service_ptr const
sge::window::instance::awl_io_service() const
{
	return io_service_;
}
