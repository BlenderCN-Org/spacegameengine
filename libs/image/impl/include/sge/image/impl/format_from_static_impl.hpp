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


#ifndef SGE_IMAGE_IMPL_FORMAT_FROM_STATIC_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_FORMAT_FROM_STATIC_IMPL_HPP_INCLUDED

#include <sge/image/enable_if_has_format.hpp>
#include <sge/image/format_from_static.hpp>
#include <sge/image/impl/static_to_dynamic_format.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>


template<
	typename Tag,
	typename Format
>
sge::image::enable_if_has_format<
	Tag,
	Format,
	sge::image::traits::pixel::format<
		Tag
	>
>
sge::image::format_from_static()
{
	return
		sge::image::impl::static_to_dynamic_format<
			Tag,
			Format
		>::value;
}

#endif
