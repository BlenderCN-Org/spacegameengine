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


#include <sge/opengl/convert/color_to_format_type.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/common.hpp>
#include <sge/image/color/format.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::opengl::color_format_type const
sge::opengl::convert::color_to_format_type(
	image::color::format::type const _fmt
)
{
	switch(
		_fmt
	)
	{
	case image::color::format::a8:
	case image::color::format::l8:
	case image::color::format::la8:
	case image::color::format::rgb8:
	case image::color::format::bgr8:
	case image::color::format::rgba8:
	case image::color::format::bgra8:
		return
			opengl::color_format_type(
				GL_UNSIGNED_BYTE
			);
	case image::color::format::rgb32f:
	case image::color::format::bgr32f:
	case image::color::format::rgba32f:
	case image::color::format::bgra32f:
		return
			opengl::color_format_type(
				GL_FLOAT
			);
	case image::color::format::size:
	case image::color::format::rgbx8:
	case image::color::format::bgrx8:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
