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


#include <sge/libpng/color_type_from_format.hpp>
#include <sge/libpng/format.hpp>
#include <sge/libpng/png.hpp>
#include <fcppt/assert/unreachable.hpp>


int
sge::libpng::color_type_from_format(
	sge::libpng::format const _format
)
{
	switch(
		_format
	)
	{
	case sge::libpng::format::l8:
		return
			PNG_COLOR_TYPE_GRAY;
	case sge::libpng::format::la8:
		return
			PNG_COLOR_TYPE_GRAY_ALPHA;
	case sge::libpng::format::rgba8:
	case sge::libpng::format::bgra8:
		return
			PNG_COLOR_TYPE_RGB_ALPHA;
	case sge::libpng::format::rgb8:
	case sge::libpng::format::rgbx8:
	case sge::libpng::format::bgrx8:
	case sge::libpng::format::bgr8:
		return
			PNG_COLOR_TYPE_RGB;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
