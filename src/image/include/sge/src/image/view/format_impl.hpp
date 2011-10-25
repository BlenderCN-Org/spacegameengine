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


#ifndef SGE_SRC_IMAGE_VIEW_FORMAT_IMPL_HPP_INCLUDED
#define SGE_SRC_IMAGE_VIEW_FORMAT_IMPL_HPP_INCLUDED

#include <sge/image/view/format.hpp>
#include <sge/src/image/view/format_any.hpp>


template<
	typename Tag
>
sge::image::color::format::type
sge::image::view::format(
	typename image::traits::view<
		Tag
	>::type const &_view
)
{
	return
		image::view::format_any(
			_view
		);

}

template<
	typename Tag
>
sge::image::color::format::type
sge::image::view::format(
	typename image::traits::const_view<
		Tag
	>::type const &_view
)
{
	return
		image::view::format_any(
			_view
		);
}

#endif