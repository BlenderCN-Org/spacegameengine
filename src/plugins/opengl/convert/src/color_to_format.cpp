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


#include "../color_to_format.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::opengl::color_format const
sge::opengl::convert::color_to_format(
	image::color::format::type const _fmt
)
{
	switch(
		_fmt
	)
	{
	case image::color::format::gray8:
		return
			opengl::color_format(
				GL_LUMINANCE
			);
	case image::color::format::alpha8:
		return
			opengl::color_format(
				GL_ALPHA
			);
	case image::color::format::rgba8:
	case image::color::format::rgba32f:
		return
			opengl::color_format(
				GL_RGBA
			);
	case image::color::format::rgb8:
	case image::color::format::rgb32f:
		return
			opengl::color_format(
				GL_RGB
			);
	case image::color::format::argb8:
	case image::color::format::argb32f:
	case image::color::format::bgra8:
	case image::color::format::bgra32f:
		return
			opengl::color_format(
				GL_BGRA
			);
	case image::color::format::size:
		break;
	}

	throw renderer::exception(
		FCPPT_TEXT("Invalid color_format in color_to_format()!")
	);
}
