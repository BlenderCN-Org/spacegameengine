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


#include <sge/opengl/texture/buffer_surface_types.hpp>
#include <sge/opengl/texture/funcs/set_2d.hpp>
#include <sge/opengl/texture/funcs/set_rect.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/make_ref.hpp>


sge::renderer::size_type
sge::opengl::texture::buffer_surface_types::min_size()
{
	return
		64u;
}

sge::opengl::texture::buffer_surface_types::init_function_type
sge::opengl::texture::buffer_surface_types::init_function()
{
	return
		fcppt::make_ref(
			sge::opengl::texture::funcs::set_2d
		);
}

sge::opengl::texture::buffer_surface_types::sub_function_type
sge::opengl::texture::buffer_surface_types::sub_function()
{
	return
		fcppt::make_ref(
			sge::opengl::texture::funcs::set_rect
		);
}
