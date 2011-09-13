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


#include "../best_il_format.hpp"
#include <sge/image/color/format.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::image::color::format::type
sge::devil::best_il_format(
	image::color::format::type const _format
)
{
	switch(
		_format
	)
	{
	case image::color::format::a8:
	case image::color::format::l8:
	case image::color::format::la8:
	case image::color::format::rgb8:
	case image::color::format::bgr8:
	case image::color::format::rgba8:
	case image::color::format::bgra8:
	case image::color::format::rgb32f:
	case image::color::format::bgr32f:
	case image::color::format::rgba32f:
	case image::color::format::bgra32f:
		return _format;
	case image::color::format::rgbx8:
		return image::color::format::rgb8;
	case image::color::format::bgrx8:
		return image::color::format::bgr8;
	case image::color::format::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE
}
