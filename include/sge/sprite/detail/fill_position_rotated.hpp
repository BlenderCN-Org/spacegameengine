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


#ifndef SGE_SPRITE_DETAIL_FILL_POSITION_ROTATED_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_POSITION_ROTATED_HPP_INCLUDED

#include <sge/sprite/detail/point_float.hpp>
#include <sge/sprite/detail/rect_float.hpp>
#include <sge/sprite/detail/vertices_per_sprite.hpp>
#include <sge/sprite/detail/depth.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/bounding_rect.hpp>
#include <sge/sprite/depth_type.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/construct.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/tr1/array.hpp>
#include <boost/foreach.hpp>
#include <cmath>

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
fill_position_rotated(
	Iterator iterator,
	object<
		Choices
	> const &spr
)
{
	typedef typename Choices::type_choices type_choices;

	typedef typename type_choices::float_type funit;

	typedef typename detail::point_float<
		type_choices
	>::type pos2;

	pos2 const centerf(
		fcppt::math::vector::structure_cast<
			pos2
		>(
			spr.rotation_center()
		)
	);

	typedef typename detail::rect_float<
		type_choices
	>::type float_rect;

	float_rect const rbs(
		fcppt::math::box::structure_cast<
			float_rect
		>(
			sprite::bounding_rect(
				spr
			)
		)
	);

	typedef std::tr1::array<
		pos2,
		detail::vertices_per_sprite
	> position_array;

	position_array const positions = {{
		pos2(
			rbs.left(),
			rbs.top()
		) - centerf,
		pos2(
			rbs.right(),
			rbs.top()
		) - centerf,
		pos2(
			rbs.right(),
			rbs.bottom()
		) - centerf,
		pos2(
			rbs.left(),
			rbs.bottom()
		) - centerf
	}};

	typedef typename sprite::rotation_type<
		funit
	>::type rotation_type;
	
	rotation_type const rot(
		spr.rotation()
	);

	funit const
		sinx = std::sin(rot),
		cosx = std::cos(rot);

	typedef typename fcppt::math::matrix::static_<
		funit,
		2,
		2
	>::type matrix2x2;
	
	matrix2x2 const mat_rot(
		cosx, -sinx,
		sinx,  cosx
	);

	typedef typename detail::vertex_pos<
		type_choices
	>::type vertex_pos;

	typedef typename sprite::depth_type<
		funit
	>::type depth_type;

	depth_type const depth_(
		depth(
			spr
		)
	);

	BOOST_FOREACH(
		typename position_array::const_reference ref,
		positions
	)
		(*iterator++). template set<
			vertex_pos
		>(
			construct(
				(mat_rot * ref) + centerf,
				depth_
			)
		);
}

}
}
}

#endif
