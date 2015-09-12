/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/create_depth_stencil_surface.hpp>
#include <sge/opengl/fbo/depth_stencil_surface.hpp>
#include <sge/opengl/fbo/get_config.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::depth_stencil_buffer::surface_unique_ptr
sge::opengl::fbo::create_depth_stencil_surface(
	sge::opengl::context::system::object &_context,
	sge::renderer::depth_stencil_buffer::surface_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::depth_stencil_buffer::surface
		>(
			fcppt::make_unique_ptr<
				sge::opengl::fbo::depth_stencil_surface
			>(
				sge::opengl::fbo::get_config(
					sge::opengl::context::use<
						sge::opengl::fbo::context
					>(
						_context
					)
				),
				_parameters
			)
		);
}
