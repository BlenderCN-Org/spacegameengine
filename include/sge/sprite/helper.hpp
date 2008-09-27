/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_HELDER_HPP_INCLUDED
#define SGE_SPRITE_HELDER_HPP_INCLUDED

#include "types.hpp"
#include "vertex_format.hpp"
#include "../renderer/vf/iterator.hpp"
#include "../renderer/index_view.hpp"
#include "../export.hpp"
#include "../math/rect.hpp"

namespace sge
{
namespace sprite
{

typedef renderer::index_view_16 index_view;
typedef renderer::vf::iterator<vertex_format> vertex_iterator;

SGE_SYMBOL vertex_iterator
fill_position(
	vertex_iterator,
	rect const &rs,
	depth_type z);

SGE_SYMBOL vertex_iterator
fill_tex_coordinates(
	vertex_iterator,
	tex_rect const &rt);

SGE_SYMBOL vertex_iterator
fill_vertices(
	vertex_iterator it,
	rect const &rs,
	tex_rect const &rt,
	depth_type z);

SGE_SYMBOL vertex_iterator
fill_position_rotated(
	vertex_iterator it,
	rect const &rbs,
	rotation_type rot,
	point const &center,
	depth_type z);

SGE_SYMBOL vertex_iterator
fill_color(
	vertex_iterator it,
	color col);

SGE_SYMBOL index_view::iterator
fill_indices(
	index_view::iterator it,
	index_view::value_type start);

}
}

#endif
