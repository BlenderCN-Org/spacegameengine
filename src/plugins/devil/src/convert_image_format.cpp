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


#include "../convert_image_format.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

ILuint
sge::devil::convert_image_format(
	image::format::type const t
)
{
	switch(t)
	{
	case image::format::bmp:
		return IL_BMP;
	case image::format::gif:
		return IL_GIF;
	case image::format::jpeg:
		return IL_JPG;
	case image::format::png:
		return IL_PNG;
	case image::format::tiff:
		return IL_TIF;
	case image::format::tga:
		return IL_TGA;
	}

	throw exception(
		FCPPT_TEXT("Invalid image_format!")
	);
}
