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


#ifndef SGE_RENDERER_CONST_SCOPED_BUFFER_LOCK_IMPL_HPP_INCLUDED
#define SGE_RENDERER_CONST_SCOPED_BUFFER_LOCK_IMPL_HPP_INCLUDED

#include <sge/renderer/detail/const_scoped_buffer_lock.hpp>

template<
	typename Ptr,
	typename View
>
sge::renderer::detail::const_scoped_buffer_lock<Ptr, View>::const_scoped_buffer_lock(
	Ptr const ptr,
	size_type const first,
	size_type const count)
:
	ptr(ptr),
	view(
		ptr->lock(
			first,
			count))
{}

template<
	typename Ptr,
	typename View
>
View const
sge::renderer::detail::const_scoped_buffer_lock<Ptr, View>::value() const
{
	return view;
}

template<
	typename Ptr,
	typename View
>
sge::renderer::detail::const_scoped_buffer_lock<Ptr, View>::~const_scoped_buffer_lock()
{
	ptr->unlock();
}

#endif
