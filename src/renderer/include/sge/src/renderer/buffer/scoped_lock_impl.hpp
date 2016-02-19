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


#ifndef SGE_SRC_RENDERER_BUFFER_SCOPED_LOCK_IMPL_HPP_INCLUDED
#define SGE_SRC_RENDERER_BUFFER_SCOPED_LOCK_IMPL_HPP_INCLUDED

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/buffer/scoped_lock.hpp>
#include <sge/renderer/buffer/writable.hpp>


template<
	typename Tag
>
sge::renderer::buffer::scoped_lock<
	Tag
>::scoped_lock(
	buffer_type &_buffer,
	sge::renderer::lock_mode const _mode
)
:
	buffer_(
		_buffer
	),
	view_(
		buffer_.lock(
			_mode
		)
	)
{
}

template<
	typename Tag
>
sge::renderer::buffer::scoped_lock<
	Tag
>::scoped_lock(
	buffer_type &_buffer,
	lock_area const &_area,
	sge::renderer::lock_mode const _mode
)
:
	buffer_(
		_buffer
	),
	view_(
		buffer_.lock(
			_area,
			_mode
		)
	)
{
}

template<
	typename Tag
>
typename
sge::renderer::buffer::scoped_lock<
	Tag
>::view
sge::renderer::buffer::scoped_lock<
	Tag
>::value() const
{
	return
		view_;
}

template<
	typename Tag
>
sge::renderer::buffer::scoped_lock<
	Tag
>::~scoped_lock()
{
	buffer_.unlock();
}

#endif
