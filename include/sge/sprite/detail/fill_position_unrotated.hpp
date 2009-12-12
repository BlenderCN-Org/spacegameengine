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


#ifndef SGE_SPRITE_DETAIL_FILL_POSITION_UNROTATED_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_POSITION_UNROTATED_HPP_INCLUDED

#include <sge/sprite/detail/vertex_pos.hpp>
#include <sge/sprite/detail/rect_float.hpp>
#include <sge/sprite/detail/point_float3.hpp>
#include <sge/sprite/detail/depth.hpp>
#include <sge/sprite/depth_type.hpp>
#include <sge/sprite/bounding_rect.hpp>
#include <sge/math/box/structure_cast.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Iterator,
	typename Choices
>
void
fill_position_unrotated(
	Iterator iterator,
	object<
		Choices
	> const &spr
)
{
	typedef typename Choices::type_choices type_choices;

	typedef typename detail::vertex_pos<
		type_choices
	>::type vertex_pos;

	typedef typename detail::rect_float<
		type_choices
	>::type rect_float;

	rect_float const rect_(
		math::box::structure_cast<
			rect_float
		>(
			sprite::bounding_rect(
				spr
			)
		)
	);

	typedef typename point_float3<
		type_choices
	>::type pos3;

	typedef typename sprite::depth_type<
		typename type_choices::float_type
	>::type depth_type;

	depth_type const depth_(
		depth(
			spr
		)
	);

	(*iterator++). template set<
		vertex_pos
	>(
		pos3(
			rect_.left(),
			rect_.top(),
			depth_
		)
	);

	(*iterator++). template set<
		vertex_pos
	>(
		pos3(
			rect_.right(),
			rect_.top(),
			depth_
		)
	);

	(*iterator++). template set<
		vertex_pos
	>(
		pos3(
			rect_.right(),
			rect_.bottom(),
			depth_
		)
	);

	(*iterator++). template set<
		vertex_pos
	>(
		pos3(
			rect_.left(),
			rect_.bottom(),
			depth_
		)
	);
}

}
}
}

#endif
