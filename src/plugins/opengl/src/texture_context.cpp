/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../texture_context.hpp"
#include "../context/make_id.hpp"
#include "../glew/is_supported.hpp"

sge::opengl::texture_context::texture_context()
:
	anisotropic_filter_supported_(
		sge::opengl::glew::is_supported(
			"GL_EXT_texture_filter_anisotropic"
		)
	),
	generate_mipmap_flag_supported_(
		sge::opengl::glew::is_supported(
			"GL_VERSION_1_4"
		)
	)
{}

sge::opengl::texture_context::~texture_context()
{
}

bool
sge::opengl::texture_context::anisotropic_filter_supported() const
{
	return anisotropic_filter_supported_;
}

bool
sge::opengl::texture_context::generate_mipmap_flag_supported() const
{
	return generate_mipmap_flag_supported_;
}

sge::opengl::context::id const
sge::opengl::texture_context::static_id(
	sge::opengl::context::make_id()
);
