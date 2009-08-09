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


#include "blit.hpp"
#include "normalization.hpp"
#include <sge/math/rect/intersection.hpp>
#include <sge/math/rect/structure_cast.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/algorithm/transform.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/assert.hpp>
#include <mizuiro/color/for_each_channel.hpp>
#include <algorithm>

namespace
{

template<
	typename Source,
	typename DstPixel
>
class channel_blitter {
public:
	typedef typename DstPixel::layout::channel_type channel_type;

	channel_blitter(
		Source const &src,
		channel_type const src_alpha,
		channel_type const dest_alpha,
		DstPixel const &result
	);

	typedef void result_type;

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
	Source const src;
	channel_type const src_alpha,dest_alpha;
	DstPixel const &result;
};

template<
	typename Source,
	typename DstPixel
>
channel_blitter<
	Source,
	DstPixel
>::channel_blitter(
	Source const &src,
	channel_type const src_alpha,
	channel_type const dest_alpha,
	DstPixel const &result)
:
	src(src),
	src_alpha(src_alpha),
	dest_alpha(dest_alpha),
	result(result)
{}

template<
	typename Source,
	typename DstPixel
>
template<
	typename Channel
>
typename channel_blitter<
	Source,
	DstPixel
>::result_type
channel_blitter<
	Source,
	DstPixel
>::operator()(
	Channel &
) const
{
	float const src_floating = sge::gui::utility::normalize<float>(src_alpha);
	float const dest_floating = sge::gui::utility::normalize<float>(dest_alpha);

	result. template set<Channel>(
		static_cast<channel_type>(
			static_cast<float>(src. template get<Channel>())
			* src_floating
			+ static_cast<float>(result. template get<Channel>())
			* std::max(
				dest_floating - src_floating,
				0.0f
			)
		)
	);
}

template<
	typename Source,
	typename DstPixel
>
typename channel_blitter<
	Source,
	DstPixel
>::result_type
channel_blitter<
	Source,
	DstPixel
>::operator()(
	mizuiro::color::channel::alpha &	
) const
{
	typedef mizuiro::color::channel::alpha alpha;

	result. template set<alpha>(
		src. template get<alpha>()
		+ result. template get<alpha>()
		> DstPixel::layout:: template channel_max<alpha>()
		?
			DstPixel::layout:: template channel_max<alpha>()
		:
			static_cast<
				channel_type
			>(
				src. template get<alpha>()
				+ result. template get<alpha>()
			)
	);
}

class blitter {
public:
	typedef void result_type;

	template<
		typename Src,
		typename Dst
	>
	result_type
	operator()(
		Src const &src_color,
		Dst const &dst_color
	) const;
};

template<
	typename Src,
	typename Dst
>
blitter::result_type
blitter::operator()(
	Src const &src_color,
	Dst const &result
) const
{
	mizuiro::color::for_each_channel<
		typename Dst::layout
	>(
		// TODO: replace this with something like std::make_pair!
		channel_blitter<
			mizuiro::color::object<
				typename Dst::layout
			>,
			Dst
		>(
			sge::image::color::convert<
				typename Dst::layout
			>(
				src_color
			),
			sge::image::color::convert<
				typename Dst::layout
			>(
				src_color
			). template get<mizuiro::color::channel::alpha>(),
			result. template get<mizuiro::color::channel::alpha>(),
			result
		)
	);
}
}

void sge::gui::utility::blit_invalid(
	const_image_view const &src,
	rect const &src_rect,
	image_view const dst,
	rect const &dst_rect,
	bool transparency)
{
	// Calculate intersection of source and destination
	rect const is = intersection(
		src_rect,
		dst_rect);
	
	// No intersection? then leave now.
	if (is == rect::null())
		return;

	// Move intersection rect to origin of invalid rect
	rect const is_translated_dst(
		is.pos()-dst_rect.pos(),
		is.dim());

	rect const is_translated_src(
		is.pos()-src_rect.pos(),
		is.dim());

	if (transparency)
	{
		sge::image::algorithm::transform(
			sge::image::view::sub(
				src,
				math::rect::structure_cast<
					sge::image::rect
				>(
					is_translated_src
				)
			),
			sge::image::view::sub(
				dst,
				math::rect::structure_cast<
					sge::image::rect
				>(
					is_translated_dst
				)
			),
			blitter()
		);
	}
	else
	{
		sge::image::algorithm::copy_and_convert(
			sge::image::view::sub(
				src,
				math::rect::structure_cast<
					sge::image::rect
				>(
					is_translated_src
				)
			),
			sge::image::view::sub(
				dst,
				math::rect::structure_cast<
					sge::image::rect
				>(
					is_translated_dst
				)
			)
		);
	}
}

void sge::gui::utility::blit(
	const_image_view const &src,
	rect const &src_rect,
	image_view const dst,
	rect const &dst_rect,
	rect const &clip_rect)
{
	SGE_ASSERT(src_rect.dim() == dst_rect.dim());

	rect const clipped = intersection(
		dst_rect,
		clip_rect);
	
	rect const src_trans = rect(
		clipped.pos() - dst_rect.pos(),
		clipped.dim());

	sge::image::algorithm::transform(
		sge::image::view::sub(
			sge::image::view::sub(
				src,
				math::rect::structure_cast<
					sge::image::rect
				>(
					src_rect
				)
			),
			math::rect::structure_cast<
				sge::image::rect
			>(
				src_trans
			)
		),
		sge::image::view::sub(
			dst,
			math::rect::structure_cast<
				sge::image::rect
			>(
				clipped
			)
		),
		blitter()
	);
}
