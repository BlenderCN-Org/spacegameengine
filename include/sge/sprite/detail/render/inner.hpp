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


#ifndef SGE_SPRITE_DETAIL_RENDER_INNER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_INNER_HPP_INCLUDED

#include <sge/renderer/device.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <sge/sprite/detail/geometry/indices_per_sprite.hpp>
#include <sge/sprite/detail/geometry/vertices_per_sprite.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	typename Choices,
	typename Buffers
>
typename boost::enable_if<
	sge::sprite::detail::config::needs_index_buffer<
		Choices
	>,
	void
>::type
inner(
	sge::renderer::device &_renderer,
	sge::renderer::size_type const _offset,
	sge::sprite::count const _num_objects,
	Buffers const &_buffers
)
{
	_renderer.render_indexed(
		_buffers.index_buffer(),
		sge::renderer::first_vertex(
			_offset
			*
			sge::sprite::detail::geometry::vertices_per_sprite<
				Choices
			>::value
		),
		sge::renderer::vertex_count(
			_num_objects.get()
			*
			sge::sprite::detail::geometry::vertices_per_sprite<
				Choices
			>::value
		),
		sge::renderer::indexed_primitive_type::triangle,
		sge::renderer::primitive_count(
			_num_objects.get() * 2u
		),
		sge::renderer::first_index(
			_offset
			*
			sge::sprite::detail::geometry::indices_per_sprite<
				Choices
			>::value
		)
	);
}

template<
	typename Choices,
	typename Buffers
>
typename boost::disable_if<
	sge::sprite::detail::config::needs_index_buffer<
		Choices
	>,
	void
>::type
inner(
	sge::renderer::device &_renderer,
	sge::renderer::size_type const _offset,
	sge::sprite::count const _num_objects,
	Buffers const &
)
{
	_renderer.render_nonindexed(
		sge::renderer::first_vertex(
			_offset
			*
			sge::sprite::detail::geometry::vertices_per_sprite<
				Choices
			>::value
		),
		sge::renderer::vertex_count(
			_num_objects.get()
			*
			sge::sprite::detail::geometry::vertices_per_sprite<
				Choices
			>::value
		),
		sge::renderer::nonindexed_primitive_type::point
	);
}

}
}
}
}

#endif
