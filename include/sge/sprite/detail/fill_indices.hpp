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


#ifndef SGE_SPRITE_DETAIL_FILL_INDICES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_INDICES_HPP_INCLUDED

#include <sge/sprite/detail/indices_per_sprite.hpp>
#include <sge/sprite/detail/index_generator.hpp>
#include <sge/renderer/index/any/generate.hpp>
#include <sge/renderer/index/any/make_view.hpp>
#include <sge/renderer/index_buffer_ptr.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/size_type.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices
>
void
fill_indices(
	sge::renderer::index_buffer_ptr const _ib,
	sge::renderer::size_type const _count
)
{
	renderer::scoped_index_lock const lock(
		_ib,
		renderer::lock_mode::writeonly,
		0,
		_count
		*
		detail::indices_per_sprite<
			typename Choices::elements
		>::value
	);

	renderer::index::any::generate(
		renderer::index::any::make_view(
			lock.value()
		),
		detail::index_generator<
			Choices
		>()
	);
}

}
}
}

#endif
