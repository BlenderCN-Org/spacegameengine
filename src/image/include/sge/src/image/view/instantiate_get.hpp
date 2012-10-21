/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_IMAGE_VIEW_INSTANTIATE_GET_HPP_INCLUDED
#define SGE_SRC_IMAGE_VIEW_INSTANTIATE_GET_HPP_INCLUDED

#include <sge/image/color/any/object.hpp>
#include <sge/image/traits/const_view_fwd.hpp>
#include <sge/image/traits/dim_fwd.hpp>
#include <sge/image/traits/view_fwd.hpp>
#include <sge/src/export_function_instantiation.hpp>
#include <sge/src/image/view/data_impl.hpp>


#define SGE_SRC_IMAGE_VIEW_INSTANTIATE_GET_BASE(\
	tag,\
	view_type\
)\
template \
SGE_EXPORT_FUNCTION_INSTANTIATION \
sge::image::color::any::object const \
sge::image::view::get<\
	tag\
>(\
	sge::image::traits::view_type<\
		tag\
	>::type const &,\
	sge::image::traits::dim<\
		tag\
	>::type const &\
);

#define SGE_SRC_IMAGE_VIEW_INSTANTIATE_GET(\
	tag\
)\
SGE_SRC_IMAGE_VIEW_INSTANTIATE_GET_BASE(\
	tag,\
	view\
)\
SGE_SRC_IMAGE_VIEW_INSTANTIATE_GET_BASE(\
	tag,\
	const_view\
)

#endif
