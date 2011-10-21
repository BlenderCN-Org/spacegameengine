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


#ifndef SGE_IMAGE_VIEW_CHECKED_SUB_CONDITION_HPP_INCLUDED
#define SGE_IMAGE_VIEW_CHECKED_SUB_CONDITION_HPP_INCLUDED

#include <sge/image/traits/box.hpp>
#include <sge/image/traits/sub_out_of_range.hpp>
#include <sge/image/view/size.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/contains.hpp>


namespace sge
{
namespace image
{
namespace view
{

template<
	typename Tag,
	typename View
>
void
checked_sub_condition(
	View const &_src,
	typename sge::image::traits::box<
		Tag
	>::type const &_box
)
{
	typedef typename sge::image::traits::box<
		Tag
	>::type box;

	box const outer(
		box::vector::null(),
		sge::image::view::size<
			Tag
		>(
			_src
		)
	);

	if(
		!fcppt::math::box::contains(
			outer,
			_box
		)
	)
		throw
			typename sge::image::traits::sub_out_of_range<
				Tag
			>::type(
				outer,
				_box
			);
}

}
}
}

#endif
