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


#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/convert/make_type.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/static_cast_fun.hpp>


sge::opengl::texture::type
sge::opengl::texture::convert::make_type(
	int const _type
)
{
	// TODO: Template
	return
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::type,
			fcppt::cast::static_cast_fun
		>(
			_type
		);
}
