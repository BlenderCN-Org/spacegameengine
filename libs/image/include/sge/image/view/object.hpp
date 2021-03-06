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


#ifndef SGE_IMAGE_VIEW_OBJECT_HPP_INCLUDED
#define SGE_IMAGE_VIEW_OBJECT_HPP_INCLUDED

#include <sge/image/has_format.hpp>
#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/view/elements.hpp>
#include <sge/image/view/mizuiro_type_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>
#include <mizuiro/nonconst_tag.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace sge
{
namespace image
{
namespace view
{

template<
	typename Tag
>
class object
{
public:
	typedef
	sge::image::view::elements<
		Tag
	>
	elements;

	typedef
	fcppt::variant::object<
		elements
	>
	variant;

	template<
		typename Format
	>
	explicit
	object(
		sge::image::view::mizuiro_type<
			Format,
			mizuiro::nonconst_tag
		> const &_view
	)
	:
		object(
			variant{
				_view
			}
		)
	{
		static_assert(
			sge::image::has_format<
				sge::image::traits::image::color_tag<
					Tag
				>,
				typename
				Format::color_format
			>::value,
			"Invalid format."
		);
	}

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	explicit
	object(
		variant const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	object(
		object const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	object &
	operator=(
		object const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	~object();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	variant const &
	get() const;
private:
	variant variant_;
};

}
}
}

#endif
