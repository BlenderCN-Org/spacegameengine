/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_IMAGE_VIEW_MAKE_IMPL_HPP_INCLUDED
#define SGE_SRC_IMAGE_VIEW_MAKE_IMPL_HPP_INCLUDED

#include <sge/image/raw_pointer.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/traits/color_tag.hpp>
#include <sge/image/traits/dim_fwd.hpp>
#include <sge/image/traits/format_fwd.hpp>
#include <sge/image/traits/pitch_fwd.hpp>
#include <sge/image/traits/view_elements.hpp>
#include <sge/image/traits/view_fwd.hpp>
#include <sge/image/view/make.hpp>
#include <sge/src/image/view/make_visitor.hpp>
#include <mizuiro/image/is_raw_view.hpp>
#include <fcppt/mpl/invoke_on.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/quote.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Tag
>
typename sge::image::traits::view<
	Tag
>::type const
sge::image::view::make(
	sge::image::raw_pointer const _data,
	typename sge::image::traits::dim<
		Tag
	>::type const &_dim,
	typename sge::image::traits::format<
		typename sge::image::traits::color_tag<
			Tag
		>::type
	>::type const _format,
	typename sge::image::traits::pitch<
		Tag
	>::type const &_pitch
)
{
	return
		fcppt::mpl::invoke_on<
			boost::mpl::filter_view<
				typename sge::image::traits::view_elements<
					Tag
				>::type,
				boost::mpl::bind<
					boost::mpl::quote1<
						mizuiro::image::is_raw_view
					>,
					boost::mpl::_1
				>
			>
		>(
			static_cast<
				sge::image::size_type
			>(
				_format
			),
			sge::image::view::make_visitor<
				typename sge::image::traits::view<
					Tag
				>::type,
				typename sge::image::traits::dim<
					Tag
				>::type,
				typename sge::image::traits::pitch<
					Tag
				>::type
			>(
				_data,
				_dim,
				_pitch
			)
		);
}

#endif
