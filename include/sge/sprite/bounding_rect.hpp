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


#ifndef SGE_SPRITE_BOUNDING_RECT_HPP_INCLUDED
#define SGE_SPRITE_BOUNDING_RECT_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/rect.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


namespace sge
{
namespace sprite
{

template<
	typename Choices
>
typename rect<
	typename Choices::type_choices::unit_type
>::type const
bounding_rect(
	object<
		Choices
	> const &_sprite
)
{
	return
		typename sprite::rect<
			typename Choices::type_choices::unit_type
		>::type(
			_sprite.pos(),
			_sprite.size()
		);
}

}
}

#endif
