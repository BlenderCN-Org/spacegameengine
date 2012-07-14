/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_IMAGE_DYNAMIC_COLOR_FROM_STATIC_FORMAT_HPP_INCLUDED
#define SGE_SRC_IMAGE_DYNAMIC_COLOR_FROM_STATIC_FORMAT_HPP_INCLUDED

#include <sge/image/symbol.hpp>
#include <sge/image/color/a8_format.hpp>
#include <sge/image/color/bgr32f_format.hpp>
#include <sge/image/color/bgr8_format.hpp>
#include <sge/image/color/bgra32f_format.hpp>
#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/bgrx8_format.hpp>
#include <sge/image/color/l8_format.hpp>
#include <sge/image/color/la8_format.hpp>
#include <sge/image/color/r32f_format.hpp>
#include <sge/image/color/rgb32f_format.hpp>
#include <sge/image/color/rgb8_format.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/rgbx8_format.hpp>
#include <sge/image/color/srgb8_format.hpp>
#include <sge/image/color/srgb32f_format.hpp>
#include <sge/src/image/dynamic/color/c32f_1_format.hpp>
#include <sge/src/image/dynamic/color/c32f_3_format.hpp>
#include <sge/src/image/dynamic/color/c32f_4_format.hpp>
#include <sge/src/image/dynamic/color/c8_1_format.hpp>
#include <sge/src/image/dynamic/color/c8_2_format.hpp>
#include <sge/src/image/dynamic/color/c8_3_format.hpp>
#include <sge/src/image/dynamic/color/c8_4_format.hpp>


namespace sge
{
namespace image
{
namespace dynamic
{
namespace color
{

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c8_1_format const &
from_static_format(
	sge::image::color::a8_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c8_1_format const &
from_static_format(
	sge::image::color::l8_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c32f_1_format const &
from_static_format(
	sge::image::color::r32f_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c8_2_format const &
from_static_format(
	sge::image::color::la8_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c8_3_format const &
from_static_format(
	sge::image::color::rgb8_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c8_3_format const &
from_static_format(
	sge::image::color::bgr8_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c8_4_format const &
from_static_format(
	sge::image::color::rgba8_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c8_4_format const &
from_static_format(
	sge::image::color::rgbx8_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c8_4_format const &
from_static_format(
	sge::image::color::bgra8_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c8_4_format const &
from_static_format(
	sge::image::color::bgrx8_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c32f_3_format const &
from_static_format(
	sge::image::color::rgb32f_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c32f_3_format const &
from_static_format(
	sge::image::color::bgr32f_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c32f_4_format const &
from_static_format(
	sge::image::color::rgba32f_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c32f_4_format const &
from_static_format(
	sge::image::color::bgra32f_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c8_3_format const &
from_static_format(
	sge::image::color::srgb8_format const &
);

SGE_IMAGE_SYMBOL
sge::image::dynamic::color::c32f_3_format const &
from_static_format(
	sge::image::color::srgb32f_format const &
);

}
}
}
}

#endif
