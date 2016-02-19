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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_ALGORITHM_CAC_RGB_TO_SRGB_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_ALGORITHM_CAC_RGB_TO_SRGB_HPP_INCLUDED

#include <mizuiro/color/space/rgb.hpp>
#include <mizuiro/color/space/srgb.hpp>
#include <mizuiro/color/types/space.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/and.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace dynamic
{
namespace algorithm
{
namespace cac
{

// TODO: Simplify this?
template<
	typename SourceFormat,
	typename DestFormat
>
using
rgb_to_srgb
=
boost::mpl::and_<
	std::is_same<
		mizuiro::color::types::space<
			typename
			DestFormat::color_format
		>,
		mizuiro::color::space::rgb
	>,
	std::is_same<
		mizuiro::color::types::space<
			typename
			SourceFormat::color_format
		>,
		mizuiro::color::space::srgb
	>
>;

}
}
}
}
}
}

#endif
