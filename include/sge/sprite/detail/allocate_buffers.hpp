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


#ifndef SGE_SPRITE_DETAIL_ALLOCATE_BUFFERS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_ALLOCATE_BUFFERS_HPP_INCLUDED

#include <sge/sprite/detail/allocate_index_buffer.hpp>
#include <sge/sprite/detail/allocate_vertex_buffer.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/size_type.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Elements,
	typename DynVertex,
	typename Buffers
>
typename boost::enable_if<
	boost::mpl::contains<
		Elements,
		sprite::with_dim
	>,
	void
>::type
allocate_buffers(
	sge::renderer::device_ptr const _renderer,
	DynVertex const &_format,
	sge::renderer::size_type const _num_sprites,
	Buffers &_buffers
)
{
	detail::allocate_vertex_buffer<
		Elements
	>(
		_renderer,
		_format,
		_num_sprites,
		_buffers
	);

	detail::allocate_index_buffer<
		Elements
	>(
		_renderer,
		_num_sprites,
		_buffers
	);
}

template<
	typename Elements,
	typename DynVertex,
	typename Buffers
>
typename boost::disable_if<
	boost::mpl::contains<
		Elements,
		sprite::with_dim
	>,
	void
>::type
allocate_buffers(
	sge::renderer::device_ptr const _renderer,
	DynVertex const &_format,
	sge::renderer::size_type const _num_sprites,
	Buffers &_buffers
)
{
	detail::allocate_vertex_buffer<
		Elements
	>(
		_renderer,
		_format,
		_num_sprites,
		_buffers
	);
}

}
}
}

#endif