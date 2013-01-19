/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/convert/make_buffer_type.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>


sge::opengl::texture::buffer_type const
sge::opengl::texture::convert::make_buffer_type(
	int const _type
)
{
	return
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::buffer_type
		>(
			_type
		);
}
