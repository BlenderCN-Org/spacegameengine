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


#include <sge/opengl/device.hpp>
#include <sge/opengl/system.hpp>
#include <sge/opengl/backend/create_system.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/platform/create_system.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/ffp_unique_ptr.hpp>
#include <sge/renderer/device/parameters.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/object_fwd.hpp>


sge::opengl::system::system(
	fcppt::log::object &_log,
	awl::system::object &_awl_system
)
:
	sge::renderer::system::system(),
	log_{
		_log
	},
	platform_system_(
		sge::opengl::platform::create_system(
			_awl_system
		)
	),
	backend_system_(
		sge::opengl::backend::create_system(
			_awl_system
		)
	)
{
}

sge::opengl::system::~system()
{
}

sge::renderer::device::core_unique_ptr
sge::opengl::system::create_core_renderer(
	sge::renderer::device::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::device::core
		>(
			this->create_ffp_renderer(
				_parameters
			)
		);
}

sge::renderer::device::ffp_unique_ptr
sge::opengl::system::create_ffp_renderer(
	sge::renderer::device::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::device::ffp
		>(
			fcppt::make_unique_ptr<
				sge::opengl::device
			>(
				log_,
				_parameters.display_mode(),
				_parameters.window(),
				*platform_system_,
				*backend_system_
			)
		);
}

awl::visual::object_unique_ptr
sge::opengl::system::create_visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		backend_system_->create_visual(
			_pixel_format
		);
}
