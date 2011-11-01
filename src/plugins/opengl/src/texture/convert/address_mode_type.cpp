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


#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/convert/address_mode_type.hpp>
#include <sge/renderer/texture/address_mode_s.hpp>
#include <sge/renderer/texture/address_mode_t.hpp>
#include <sge/renderer/texture/address_mode_u.hpp>


GLenum
sge::opengl::texture::convert::address_mode_type<
	sge::renderer::texture::address_mode_s
>::get()
{
	return GL_TEXTURE_WRAP_S;
}

GLenum
sge::opengl::texture::convert::address_mode_type<
	sge::renderer::texture::address_mode_t
>::get()
{
	return GL_TEXTURE_WRAP_T;
}

GLenum
sge::opengl::texture::convert::address_mode_type<
	sge::renderer::texture::address_mode_u
>::get()
{
	return GL_TEXTURE_WRAP_R;
}
