/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/extract_bit_depth.hpp>
#include <sge/opengl/system.hpp>
#include <sge/opengl/convert/depth_buffer.hpp>
#include <sge/opengl/convert/stencil_buffer.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/window/to_awl_parameters.hpp>
#include <awl/system/object.hpp>
#include <awl/window/instance.hpp>
#include <awl/window/instance_shared_ptr.hpp>
#include <awl/window/parameters.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>


sge::opengl::system::system()
{
}

sge::opengl::system::~system()
{
}

sge::renderer::device_ptr const
sge::opengl::system::create_renderer(
	renderer::parameters const &_param,
	renderer::adapter const _adapter,
	awl::window::instance &_wnd
)
{
	return
		fcppt::make_shared_ptr<
			sge::opengl::device
		>(
			_param,
			_adapter,
			fcppt::ref(
				_wnd
			)
		);
}

awl::window::instance_shared_ptr const
sge::opengl::system::create_window(
	awl::system::object &_system,
	sge::window::parameters const &_wparam,
	sge::renderer::parameters const &_rparam
)
{
	return
		awl::window::instance_shared_ptr(
			_system.create(
				sge::window::to_awl_parameters(
					_wparam
				)
				.has_opengl(
					true
				)
				.bit_depth(
					opengl::extract_bit_depth(
						_rparam.screen_mode()
					)
				)
				.stencil_buffer(
					opengl::convert::stencil_buffer(
						_rparam.depth_stencil_buffer()
					)
				)
				.depth_buffer(
					opengl::convert::depth_buffer(
						_rparam.depth_stencil_buffer()
					)
				)
			)
		);
}
