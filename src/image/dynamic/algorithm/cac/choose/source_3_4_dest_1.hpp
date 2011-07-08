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


#ifndef SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_CHOOSE_SOURCE_3_4_DEST_1_HPP_INCLUDED
#define SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_CHOOSE_SOURCE_3_4_DEST_1_HPP_INCLUDED

#include "format_has_size.hpp"
#include "no_match.hpp"
#include "../function.hpp"
#include "../source.hpp"
#include "../../../color/available_channels.hpp"
#include "../../../view/format_channel.hpp"
#include <mizuiro/color/conversion/any_to_alpha.hpp>
#include <mizuiro/color/conversion/rgb_to_luminance.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace image
{
namespace dynamic
{
namespace algorithm
{
namespace cac
{

template<
	typename SourceFormat,
	typename DestFormat
>
typename boost::enable_if<
	boost::mpl::and_<
		boost::mpl::or_<
			cac::format_has_size<
				SourceFormat,
				3
			>,
			cac::format_has_size<
				SourceFormat,
				4
			>
		>,
		cac::format_has_size<
			DestFormat,
			1
		>
	>,
	typename cac::function<
		SourceFormat,
		DestFormat
	>::type
>::type
choose(
	SourceFormat const &,
	DestFormat const &_dest_format
)
{
	switch(
		dynamic::view::format_channel(
			_dest_format,
			0
		)
	)
	{
	// rgb to alpha8
	case dynamic::color::available_channels::alpha:
		return
			&mizuiro::color::conversion::any_to_alpha<
				typename DestFormat::color_format,
				typename cac::source<
					SourceFormat
				>::type
			>;
	// rgb to gray8
	case dynamic::color::available_channels::luminance:
		return
			&mizuiro::color::conversion::rgb_to_luminance<
				typename DestFormat::color_format,
				typename cac::source<
					SourceFormat
				>::type
			>;
	case dynamic::color::available_channels::red:
	case dynamic::color::available_channels::green:
	case dynamic::color::available_channels::blue:
	case dynamic::color::available_channels::undefined:
	case dynamic::color::available_channels::size:
		break;
	}

	SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_CHOOSE_NO_MATCH
}

}
}
}
}
}

#endif
