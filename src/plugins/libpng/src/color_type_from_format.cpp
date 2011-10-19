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


#include "../color_type_from_format.hpp"
#include "../png.hpp"
#include <sge/image/color/format.hpp>
#include <sge/image/unsupported_format.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

int
sge::libpng::color_type_from_format(
	fcppt::filesystem::path const &_path,
	sge::image::color::format::type const _format
)
{
	switch(
		_format
	)
	{
	case sge::image::color::format::a8:
		throw
			sge::image::unsupported_format(
				_path,
				FCPPT_TEXT("alpha8")
			);
	case sge::image::color::format::l8:
		return PNG_COLOR_TYPE_GRAY;
	case sge::image::color::format::la8:
		return PNG_COLOR_TYPE_GRAY_ALPHA;
	case sge::image::color::format::rgba8:
	case sge::image::color::format::bgra8:
		return PNG_COLOR_TYPE_RGB_ALPHA;
	case sge::image::color::format::rgb8:
	case sge::image::color::format::rgbx8:
	case sge::image::color::format::bgrx8:
	case sge::image::color::format::bgr8:
		return PNG_COLOR_TYPE_RGB;
	case sge::image::color::format::rgb32f:
	case sge::image::color::format::bgr32f:
	case sge::image::color::format::rgba32f:
	case sge::image::color::format::bgra32f:
		throw
			sge::image::unsupported_format(
				_path,
				FCPPT_TEXT("{r,g,b,a}32f")
			);
	case sge::image::color::format::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
