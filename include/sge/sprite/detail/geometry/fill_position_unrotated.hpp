/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_FILL_POSITION_UNROTATED_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_FILL_POSITION_UNROTATED_HPP_INCLUDED

#include <sge/sprite/bounding_rect.hpp>
#include <sge/sprite/detail/geometry/float_rect.hpp>
#include <sge/sprite/detail/geometry/make_position.hpp>
#include <sge/sprite/detail/vf/pos.hpp>
#include <sge/sprite/types/basic/float_vector.hpp>
#include <fcppt/math/box/structure_cast.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace geometry
{

template<
	typename Iterator,
	typename Choices
>
void
fill_position_unrotated(
	Iterator _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	typedef typename Choices::type_choices type_choices;

	typedef typename sge::sprite::detail::vf::pos<
		Choices
	>::type vertex_pos;

	typedef sge::sprite::detail::geometry::float_rect<
		type_choices
	> float_rect;

	float_rect const rect(
		fcppt::math::box::structure_cast<
			float_rect
		>(
			sge::sprite::bounding_rect(
				_sprite
			)
		)
	);

	typedef sge::sprite::types::basic::float_vector<
		type_choices
	> float_vector;

	(*_iterator++). template set<
		vertex_pos
	>(
		sge::sprite::detail::geometry::make_position<
			Choices
		>(
			float_vector(
				rect.left(),
				rect.top()
			),
			_sprite
		)
	);

	(*_iterator++). template set<
		vertex_pos
	>(
		sge::sprite::detail::geometry::make_position<
			Choices
		>(
			float_vector(
				rect.right(),
				rect.top()
			),
			_sprite
		)
	);

	(*_iterator++). template set<
		vertex_pos
	>(
		sge::sprite::detail::geometry::make_position<
			Choices
		>(
			float_vector(
				rect.right(),
				rect.bottom()
			),
			_sprite
		)
	);

	(*_iterator++). template set<
		vertex_pos
	>(
		sge::sprite::detail::geometry::make_position<
			Choices
		>(
			float_vector(
				rect.left(),
				rect.bottom()
			),
			_sprite
		)
	);
}

}
}
}
}

#endif
