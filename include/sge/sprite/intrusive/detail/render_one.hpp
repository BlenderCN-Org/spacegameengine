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


#ifndef SGE_SPRITE_INTRUSIVE_DETAIL_RENDER_ONE_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_DETAIL_RENDER_ONE_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/sprite/detail/process/geometry.hpp>
#include <sge/sprite/detail/render/range.hpp>
#include <sge/sprite/render/range_impl.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace detail
{

template<
	typename Options,
	typename Buffers,
	typename Compare,
	typename Range
>
void
render_one(
	Buffers &_buffers,
	Compare const &_compare,
	Range const &_range
)
{
	if(
		_range.empty()
	)
		return;

	typedef sge::sprite::render::range<
		typename Buffers::choices
	> range_type;

	range_type const range(
		sge::sprite::detail::process::geometry<
			Options::geometry_options,
			typename Buffers::choices
		>(
			_range,
			_buffers,
			_compare
		)
	);

	sge::renderer::device &renderer(
		_buffers.parameters().renderer()
	);

	sge::renderer::scoped_vertex_buffer const scoped_buffer(
		renderer,
		range.vertex_buffer()
	);

	sge::sprite::detail::render::range(
		renderer,
		range
	);
}

}
}
}
}

#endif
