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


#ifndef SGE_GUI_CANVAS_UTILITY_FONT_CHANNEL_BLITTER_HPP_INCLUDED
#define SGE_GUI_CANVAS_UTILITY_FONT_CHANNEL_BLITTER_HPP_INCLUDED

#include "../../utility/normalization.hpp"
#include <boost/type_traits/remove_const.hpp>

#include <iostream>

namespace sge
{
namespace gui
{
namespace utility
{

template<
	typename FontColor,
	typename FontPixel,
	typename DstPixel
>
class font_channel_blitter
{
public:
	typedef void result_type;

	typedef typename DstPixel::format::channel_type channel_type;

	typedef typename FontPixel::format::channel_type font_channel_type;

	font_channel_blitter(
		FontColor const &fontcolor,
		FontPixel const &font,
		DstPixel &result
	);

	template<
		typename Channel
	>
	result_type
	operator()(
		Channel &
	) const;

	result_type
	operator()(
		mizuiro::color::channel::alpha &
	) const;
private:
	float font_value() const;

	FontColor const &fontcolor;

	FontPixel const &font;

	DstPixel &result;
};

}
}
}

template<
	typename FontColor,
	typename FontPixel,
	typename DstPixel
>
sge::gui::utility::font_channel_blitter<
	FontColor,
	FontPixel,
	DstPixel
>::font_channel_blitter(
	FontColor const &fontcolor,
	FontPixel const &font,
	DstPixel &result
)
:
	fontcolor(fontcolor),
	font(font),
	result(result)
{}


template<
	typename FontColor,
	typename FontPixel,
	typename DstPixel
>
template<
	typename Channel
>
typename sge::gui::utility::font_channel_blitter<
	FontColor,
	FontPixel,
	DstPixel
>::result_type
sge::gui::utility::font_channel_blitter<
	FontColor,
	FontPixel,
	DstPixel
>::operator()(
	Channel &
) const
{
	std::cout << "blit other\n";
	// FIXME: add range value, divide by max-min (for font_channel_type and channel_type)
	float const font_value_(
		font_value()
	);

	std::cout << font_value_ << '\n';

	result. template set<Channel>(
		42
	/*
		static_cast<channel_type>(
			static_cast<float>(fontcolor. template get<Channel>()) * font_value_
			+ static_cast<float>(result. template get<Channel>())
			* (1.f - font_value_)
		)*/
	);
}

template<
	typename FontColor,
	typename FontPixel,
	typename DstPixel
>
typename sge::gui::utility::font_channel_blitter<
	FontColor,
	FontPixel,
	DstPixel
>::result_type
sge::gui::utility::font_channel_blitter<
	FontColor,
	FontPixel,
	DstPixel
>::operator()(
	mizuiro::color::channel::alpha &
) const
{
	std::cout << "blit alpha\n";

	std::cout << 
			font. template get<
				mizuiro::color::channel::alpha
			>()
			<< '\n';
//	std::cout << font_value() << '\n';

	result. template set<
		mizuiro::color::channel::alpha
	>(
		42
	#if 0
		denormalize<channel_type>(
			std::min(
				normalize<
					float
				>(
					result. template get<
						mizuiro::color::channel::alpha
					>()
				)
				+ font_value(),
				1.f
			)
		)
	#endif
	);
}

template<
	typename FontColor,
	typename FontPixel,
	typename DstPixel
>
float
sge::gui::utility::font_channel_blitter<
	FontColor,
	FontPixel,
	DstPixel
>::font_value() const
{
	return
		normalize<
			float
		>(
			font. template get<
				mizuiro::color::channel::alpha
			>()
		);
}

#endif
