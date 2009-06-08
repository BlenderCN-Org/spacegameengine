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


#ifndef SGE_MATH_DETAIL_VIEW_STORAGE_IMPL_HPP_INCLUDED
#define SGE_MATH_DETAIL_VIEW_STORAGE_IMPL_HPP_INCLUDED

#include <sge/math/detail/view_storage.hpp>

template<
	typename T,
	typename N
>
sge::math::detail::view_storage<T, N>::view_storage(
	pointer const rep,
	size_type const index,
	size_type const stride,
	size_type const sz)
:
	rep(rep),
	index(index),
	stride(stride),
	sz(sz)
{}

template<
	typename T,
	typename N
>
typename sge::math::detail::view_storage<T, N>::reference
sge::math::detail::view_storage<T, N>::operator[](
	size_type const i) const
{
	return rep[i * stride + index];
}
	
template<
	typename T,
	typename N
>
typename sge::math::detail::view_storage<T, N>::size_type
sge::math::detail::view_storage<T, N>::size() const
{
	return sz;
}

#endif
