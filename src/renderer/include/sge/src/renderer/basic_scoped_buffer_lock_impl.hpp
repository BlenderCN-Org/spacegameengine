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


#ifndef SGE_SRC_RENDERER_BASIC_SCOPED_BUFFER_LOCK_IMPL_HPP_INCLUDED
#define SGE_SRC_RENDERER_BASIC_SCOPED_BUFFER_LOCK_IMPL_HPP_INCLUDED

#include <sge/renderer/basic_scoped_buffer_lock.hpp>
#include <sge/renderer/lock_mode.hpp>

template<
	typename Buffer,
	typename Types
>
sge::renderer::basic_scoped_buffer_lock<
	Buffer,
	Types
>::basic_scoped_buffer_lock(
	Buffer &_buffer,
	renderer::lock_mode::type const _flags,
	first_type const _first,
	count_type const _count
)
:
	buffer_(
		_buffer
	),
	view_(
		buffer_.lock(
			_flags,
			_first,
			_count
		)
	)
{
}

template<
	typename Buffer,
	typename Types
>
typename sge::renderer::basic_scoped_buffer_lock<
	Buffer,
	Types
>::view_type const
sge::renderer::basic_scoped_buffer_lock<
	Buffer,
	Types
>::value() const
{
	return view_;
}

template<
	typename Buffer,
	typename Types
>
sge::renderer::basic_scoped_buffer_lock<
	Buffer,
	Types
>::~basic_scoped_buffer_lock()
{
	buffer_.unlock();
}

#endif
