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


#ifndef SGE_IMAGE_COLOR_IMPL_CONVERTER_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_CONVERTER_HPP_INCLUDED

#include <sge/image/color/convert.hpp>
#include <sge/image/color/invalid_convert.hpp>
#include <sge/image/color/is_convertible.hpp>
#include <sge/image/color/tag.hpp>
#include <sge/image/color/impl/traits/format_map.hpp>
#include <sge/image/impl/static_to_dynamic_format.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <mizuiro/color/object.hpp>
#include <mizuiro/color/format/argument.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace impl
{

struct converter
{
	template<
		typename DestFormat,
		typename Source
	>
	static
	std::enable_if_t<
		sge::image::color::is_convertible<
			typename
			Source::format,
			DestFormat
		>::value,
		sge::image::pixel::mizuiro_type<
			DestFormat
		>
	>
	execute(
		Source const &_source,
		typename
		mizuiro::color::object<
			DestFormat
		>::format_store_type const & =
			mizuiro::color::format::argument<
				DestFormat
			>::get()
	)
	{
		return
			sge::image::color::convert<
				DestFormat
			>(
				_source
			);
	}

	template<
		typename DestFormat,
		typename Source
	>
	static
	std::enable_if_t<
		fcppt::not_(
			sge::image::color::is_convertible<
				typename
				Source::format,
				DestFormat
			>::value
		),
		sge::image::pixel::mizuiro_type<
			DestFormat
		>
	>
	execute(
		Source const &,
		typename
		mizuiro::color::object<
			DestFormat
		>::format_store_type const & =
			mizuiro::color::format::argument<
				DestFormat
			>::get()
	)
	{
		throw
			sge::image::color::invalid_convert{
				sge::image::impl::static_to_dynamic_format<
					sge::image::color::tag,
					typename
					Source::format
				>::value,
				sge::image::impl::static_to_dynamic_format<
					sge::image::color::tag,
					DestFormat
				>::value
			};
	}
};

}
}
}
}

#endif
