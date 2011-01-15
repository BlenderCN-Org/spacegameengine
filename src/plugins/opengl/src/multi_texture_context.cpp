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


#include "../multi_texture_context.hpp"
#include "../context/make_id.hpp"
#include "../common.hpp"
#include "../glew/is_supported.hpp"
#include <algorithm>

sge::opengl::multi_texture_context::multi_texture_context()
:
	is_native_(
		glew::is_supported("GL_VERSION_1_3")
	),
	is_arb_(
		glew::is_supported("GL_ARB_multitexture")
	),
	active_texture_(
		is_native_
		?
			glActiveTexture
		:
			is_arb_
			?
				glActiveTextureARB
			:
				0
	),
	client_active_texture_(
		is_native_
		?
			glClientActiveTexture
		:
			is_arb_
			?
				glClientActiveTextureARB
			:
				0
	),
	max_level_(
		is_native_
		?
			std::max(
				GL_MAX_TEXTURE_COORDS,
				GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
			)
		:
			is_arb_
			?
				std::max(
					GL_MAX_TEXTURE_COORDS_ARB,
					GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB
				)
			:
				0
	)
{
}

sge::opengl::multi_texture_context::~multi_texture_context()
{
}

bool
sge::opengl::multi_texture_context::is_supported() const
{
	return
		is_native_
		|| is_arb_;
}

PFNGLACTIVETEXTUREPROC
sge::opengl::multi_texture_context::active_texture() const
{
	return active_texture_;
}

PFNGLCLIENTACTIVETEXTUREPROC
sge::opengl::multi_texture_context::client_active_texture() const
{
	return client_active_texture_;
}

GLint
sge::opengl::multi_texture_context::max_level() const
{
	return max_level_;
}

sge::opengl::context::id const
sge::opengl::multi_texture_context::static_id(
	sge::opengl::context::make_id()
);
