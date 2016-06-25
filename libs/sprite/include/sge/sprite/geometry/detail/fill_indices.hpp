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


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_INDICES_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_INDICES_HPP_INCLUDED

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/index/scoped_lock.hpp>
#include <sge/renderer/index/any/generate.hpp>
#include <sge/renderer/index/any/make_view.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/index_count.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <sge/sprite/geometry/detail/index_generator.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Choices
>
void
fill_indices(
	sge::sprite::count const _sprite_count,
	sge::sprite::buffers::slice<
		Choices
	> const &_slice
)
{
	sge::renderer::index::scoped_lock const lock(
		_slice.index_buffer(),
		sge::renderer::lock_segment{
			sge::renderer::lock_segment::vector{
				_slice.first_index().get()
			},
			sge::renderer::lock_segment::dim{
				sge::sprite::buffers::index_count<
					Choices
				>(
					_sprite_count
				).get()
			}
		},
		sge::renderer::lock_mode::writeonly
	);

	sge::renderer::index::any::generate(
		sge::renderer::index::any::make_view(
			lock.value()
		),
		sge::sprite::geometry::detail::index_generator<
			Choices
		>()
	);
}

}
}
}
}

#endif
