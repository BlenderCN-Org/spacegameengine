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


#ifndef SGE_IMAGE_PIXEL_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_PIXEL_CONVERT_HPP_INCLUDED

#include <sge/image/enable_if_has_format.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <sge/image/pixel/object_fwd.hpp>


namespace sge
{
namespace image
{
namespace pixel
{

template<
	typename Tag,
	typename Format
>
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
sge::image::enable_if_has_format<
	Tag,
	Format,
	sge::image::pixel::mizuiro_type<
		Format
	>
>
convert(
	sge::image::pixel::object<
		Tag
	> const &
);

}
}
}

#endif
