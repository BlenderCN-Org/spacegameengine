#ifndef SGE_GUI_UTILITY_FONT_CHANNEL_BLITTER_HPP_INCLUDED
#define SGE_GUI_UTILITY_FONT_CHANNEL_BLITTER_HPP_INCLUDED

#include "../../utility/normalization.hpp"
#include <sge/renderer/color_channel.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace sge
{
namespace gui
{
namespace utility
{
template<class DstPixel,class FontPixel>
struct font_channel_blitter 
{
	typedef typename renderer::color_channel<typename boost::remove_const<DstPixel>::type>::type channel_type;
	typedef typename renderer::color_channel<typename boost::remove_const<FontPixel>::type>::type font_channel_type;
	
	font_channel_blitter(
		DstPixel const &bgcolor,
		DstPixel const &fontcolor,
		FontPixel const &font,
		DstPixel &result);

	template<class T>
	void operator()(T &) const;
private:
	DstPixel const &bgcolor,fontcolor;
	FontPixel const &font;
	DstPixel &result;
};
}
}
}

template<class DstPixel,class FontPixel>
sge::gui::utility::font_channel_blitter<DstPixel,FontPixel>::font_channel_blitter(
	DstPixel const &bgcolor,
	DstPixel const &fontcolor,
	FontPixel const &font,
	DstPixel &result)
: bgcolor(bgcolor),
  fontcolor(fontcolor),
  font(font),
  result(result)
{}


template<class DstPixel,class FontPixel>
template<class T>
void sge::gui::utility::font_channel_blitter<DstPixel,FontPixel>::operator()(T &t) const
{
	// FIXME: add range value, divide by max-min (for font_channel_type and channel_type)
	float const font_value = normalize<float>(font[0]);

	if (t == 3)
	{
		result[t] = 
			denormalize<channel_type>(
				std::min(
					normalize<float>(bgcolor[t])+static_cast<float>(font_value),
					1.0f));
		return;
	}

	result[t] = static_cast<channel_type>(
		static_cast<float>(fontcolor[t])*font_value+
		static_cast<float>(bgcolor[t])*(1.0f-font_value));
}

#endif
