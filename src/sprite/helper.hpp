/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_SPRITE_HELDER_HPP_INCLUDED
#define SGE_SPRITE_HELDER_HPP_INCLUDED

#include <cmath>
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../renderer/transform.hpp"
#include "../math/matrix.hpp"
#include "../math/rect.hpp"

namespace sge
{

inline vertex_buffer::iterator fill_sprite_position(vertex_buffer::iterator it, const rect& rs, const space_unit z)
{
	(*it++).pos() = pos3(rs.left,rs.top,z);
	(*it++).pos() = pos3(rs.right,rs.top,z);
	(*it++).pos() = pos3(rs.right,rs.bottom,z);
	(*it++).pos() = pos3(rs.left,rs.bottom,z);

	return it;
}

inline vertex_buffer::iterator fill_sprite_tex_coordinates(vertex_buffer::iterator it, const rect& rt, const stage_type stage)
{
	(*it++).tex(stage) = tex_pos(rt.left,rt.top);
	(*it++).tex(stage) = tex_pos(rt.right,rt.top);
	(*it++).tex(stage) = tex_pos(rt.right,rt.bottom);
	(*it++).tex(stage) = tex_pos(rt.left,rt.bottom);

	return it;
}

inline vertex_buffer::iterator fill_sprite_vertices(const vertex_buffer::iterator it, const rect& rs, const rect& rt, const space_unit z, const stage_type stage = 0)
{
	fill_sprite_position(it, rs, z);
	return fill_sprite_tex_coordinates(it, rt, stage);
}

inline vertex_buffer::iterator fill_sprite_position_rotated(vertex_buffer::iterator it, const rect& rbs, const space_unit rot, const point center, const space_unit z)
{
	point one = point(rbs.left,rbs.top) - center,
	      two = point(rbs.right,rbs.top) - center,
	      three = point(rbs.right,rbs.bottom) - center,
	      four = point(rbs.left,rbs.bottom) - center;

	const space_unit sinx = std::sin(-rot),
	                 cosx = std::cos(-rot);

	const math::matrix<space_unit,2,2> mat_rot(cosx, -sinx,
	                                           sinx,  cosx); 

	one = mat_rot * one;
	two = mat_rot * two;
	three = mat_rot * three;
	four = mat_rot * four;

	one += center;
	two += center;
	three += center;
	four += center;

	(*it++).pos() = pos3(one.x(),one.y(),z);
	(*it++).pos() = pos3(two.x(),two.y(),z);
	(*it++).pos() = pos3(three.x(),three.y(),z);
	(*it++).pos() = pos3(four.x(),four.y(),z);

	return it;
}

inline vertex_buffer::iterator fill_sprite_color(vertex_buffer::iterator it, const color col)
{
	for(unsigned i = 0; i < 4; ++i)
		(*it++).diffuse() = col;
	return it;
}

inline index_buffer::iterator fill_sprite_indices(index_buffer::iterator it, const index_buffer::value_type start)
{
	(*it++) = start + 0;
	(*it++) = start + 1;
	(*it++) = start + 2;
	(*it++) = start + 0;
	(*it++) = start + 2;
	(*it++) = start + 3;

	return it;
}

}

#endif
