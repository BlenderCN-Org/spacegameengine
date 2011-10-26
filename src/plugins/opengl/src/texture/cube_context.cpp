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


#include <sge/opengl/texture/cube_context.hpp>
#include <sge/opengl/texture/cube_side_array.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/glew/is_supported.hpp>
#include <fcppt/assign/make_array.hpp>

sge::opengl::texture::cube_context::cube_context()
:
	cube_texture_normal_(
		sge::opengl::glew::is_supported("GL_VERSION_1_3")
	),
	cube_texture_arb_(
		sge::opengl::glew::is_supported("GL_ARB_texture_cube_map")
	),
	cube_texture_type_(
		cube_texture_normal_
		?
			texture::type(
				GL_TEXTURE_CUBE_MAP
			)
		:
			cube_texture_arb_
			?
				texture::type(
					GL_TEXTURE_CUBE_MAP_ARB
				)
			:
				texture::type(
					0
				)
	),
	cube_sides_(
		cube_texture_normal_
		?
			fcppt::assign::make_array<
				cube_side_array::value_type
			>
			(
				texture::type(
					GL_TEXTURE_CUBE_MAP_POSITIVE_Z
				)
			)
			(
				texture::type(
					GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
				)
			)
			(
				texture::type(
					GL_TEXTURE_CUBE_MAP_NEGATIVE_X
				)
			)
			(
				texture::type(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X
				)
			)
			(
				texture::type(
					GL_TEXTURE_CUBE_MAP_POSITIVE_Y
				)
			)
			(
				texture::type(
					GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
				)
			)
		:
			cube_texture_arb_
			?
				fcppt::assign::make_array<
					cube_side_array::value_type
				>
				(
					texture::type(
						GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
					)
				)
				(
					texture::type(
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
					)
				)
				(
					texture::type(
						GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB
					)
				)
				(
					texture::type(
						GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB
					)
				)
				(
					texture::type(
						GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB
					)
				)
				(
					texture::type(
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB
					)
				)
			:
				cube_side_array()
	)
{
}

sge::opengl::texture::cube_context::~cube_context()
{
}

bool
sge::opengl::texture::cube_context::have_cube_texture() const
{
	return
		cube_texture_normal_
		|| cube_texture_arb_;
}

sge::opengl::texture::type const
sge::opengl::texture::cube_context::cube_texture_type() const
{
	return cube_texture_type_;
}

sge::opengl::texture::cube_side_array const &
sge::opengl::texture::cube_context::cube_sides() const
{
	return cube_sides_;
}

sge::opengl::context::id const
sge::opengl::texture::cube_context::static_id(
	sge::opengl::context::make_id()
);
