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


#ifndef SGE_IMAGE_IMPL_STORE_INSTANTIATE_VIEW_HPP_INCLUDED
#define SGE_IMAGE_IMPL_STORE_INSTANTIATE_VIEW_HPP_INCLUDED

#include <sge/image/impl/store/view_impl.hpp>
#include <sge/image/traits/const_view_fwd.hpp>
#include <sge/image/traits/store_fwd.hpp>
#include <sge/image/traits/view_fwd.hpp>
#include <sge/src/core/export_function_instantiation.hpp>


#define SGE_IMAGE_IMPL_STORE_INSTANTIATE_VIEW_BASE(\
	tag,\
	ref_operator,\
	view_type\
)\
template \
SGE_CORE_EXPORT_FUNCTION_INSTANTIATION \
sge::image::traits::view_type<\
	tag\
>::type \
sge::image::store::view<\
	tag\
>(\
	sge::image::traits::store<\
		tag\
	>::type ref_operator \
)

#define SGE_IMAGE_IMPL_STORE_INSTANTIATE_VIEW(\
	tag\
)\
SGE_IMAGE_IMPL_STORE_INSTANTIATE_VIEW_BASE(\
	tag,\
	&,\
	view\
);\
SGE_IMAGE_IMPL_STORE_INSTANTIATE_VIEW_BASE(\
	tag,\
	const &,\
	const_view\
)

#endif
