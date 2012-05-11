/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/point_sprite_context.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/glew/is_supported.hpp>


sge::opengl::point_sprite_context::point_sprite_context()
:
	is_native_(
		sge::opengl::glew::is_supported(
			"GL_VERSION_2_0"
		)
	),
	is_arb_(
		sge::opengl::glew::is_supported(
			"GL_ARB_point_sprite"
		)
	),
	point_sprite_flag_(
		static_cast<
			GLenum
		>(
			is_native_
			?
				GL_POINT_SPRITE
			:
				is_arb_
				?
					GL_POINT_SPRITE_ARB
				:
					0
		)
	),
	vertex_shader_size_flag_(
		static_cast<
			GLenum
		>(
			is_native_
			?
				GL_VERTEX_PROGRAM_POINT_SIZE
			:
				is_arb_
				?
					GL_VERTEX_PROGRAM_POINT_SIZE_ARB
				:
					0
		)
	),
	coord_replace_flag_(
		static_cast<
			GLenum
		>(
			is_native_
			?
				GL_COORD_REPLACE
			:
				is_arb_
				?
					GL_COORD_REPLACE_ARB
				:
					0
		)
	)
{
}

sge::opengl::point_sprite_context::~point_sprite_context()
{
}

bool
sge::opengl::point_sprite_context::is_supported() const
{
	return
		is_native_
		|| is_arb_;
}

GLenum
sge::opengl::point_sprite_context::point_sprite_flag() const
{
	return point_sprite_flag_;
}

GLenum
sge::opengl::point_sprite_context::vertex_shader_size_flag() const
{
	return vertex_shader_size_flag_;
}

GLenum
sge::opengl::point_sprite_context::coord_replace_flag() const
{
	return coord_replace_flag_;
}

sge::opengl::context::id const
sge::opengl::point_sprite_context::static_id(
	sge::opengl::context::make_id()
);
