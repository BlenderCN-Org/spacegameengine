/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/texture/buffer_volume_types.hpp>
#include <sge/opengl/texture/funcs/set_3d.hpp>
#include <sge/opengl/texture/funcs/set_box.hpp>
#include <sge/renderer/size_type.hpp>


sge::renderer::size_type
sge::opengl::texture::buffer_volume_types::min_size()
{
	return 16u;
}

sge::opengl::texture::buffer_volume_types::init_function_type
sge::opengl::texture::buffer_volume_types::init_function()
{
	return &sge::opengl::texture::funcs::set_3d;
}

sge::opengl::texture::buffer_volume_types::sub_function_type
sge::opengl::texture::buffer_volume_types::sub_function()
{
	return &sge::opengl::texture::funcs::set_box;
}
