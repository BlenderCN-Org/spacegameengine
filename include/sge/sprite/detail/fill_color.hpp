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


#ifndef SGE_SPRITE_DETAIL_FILL_COLOR_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_COLOR_HPP_INCLUDED

#include <sge/sprite/detail/vertices_per_sprite.hpp>
#include <sge/sprite/detail/vertex_color.hpp>
#include <sge/sprite/object_impl.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Iterator,
	typename Choices,
	typename Elements
>
void
fill_color(
	Iterator iterator,
	object<
		Choices,
		Elements
	> const &sprite_
)
{
	for(
		unsigned i = 0;
		i < detail::vertices_per_sprite;
		++i
	)
		(*iterator++).set<
			typename vertex_color<
				Choices,
				Elements
			>::type
		>(
			sprite_.color()
		);
}

}
}
}

#endif
