/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_RENDER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_HPP_INCLUDED

#include <sge/sprite/detail/vertices_per_sprite.hpp>
#include <sge/sprite/detail/indices_per_sprite.hpp>
#include <sge/sprite/detail/set_texture_pre.hpp>
#include <sge/sprite/detail/set_texture.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/first_index.hpp>
#include <iterator>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename In,
	typename Comp
>
void
render(
	In const _beg,
	In const _end,
	Comp const _comp,
	renderer::device_ptr const _rend,
	renderer::index_buffer_ptr const _ib
)
{
	typedef typename std::iterator_traits<
		In
	>::value_type object_type;

	typedef typename object_type::choices choices;

	renderer::size_type offset(0);

	set_texture_pre<
		typename object_type::elements
	>(
		_rend
	);

	for(
		In cur(_beg), next(cur);
		cur != _end; cur = next
	)
	{
		renderer::size_type num_objects(0);

		while(
			next != _end && _comp(*cur, *next)
		)
		{
			++next;

			if(
				detail::visible(
					*cur
				)
			)
				++num_objects;
		}

		detail::set_texture(
			*cur,
			_rend
		);

		_rend->render(
			_ib,
			renderer::first_vertex(
				offset
				*
				detail::vertices_per_sprite<
					choices
				>::value
			),
			renderer::vertex_count(
				num_objects
				*
				detail::vertices_per_sprite<
					choices
				>::value
			),
			renderer::indexed_primitive_type::triangle,
			renderer::primitive_count(
				num_objects * 2
			),
			renderer::first_index(
				offset
				*
				detail::indices_per_sprite<
					choices
				>::value
			)
		);

		offset += num_objects;
	}
}

}
}
}

#endif
