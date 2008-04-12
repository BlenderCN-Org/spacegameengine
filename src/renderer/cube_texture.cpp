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


#include <sge/renderer/cube_texture.hpp>

template<typename BitDepth>
void sge::basic_cube_texture<BitDepth>::set_data(
	const cube_side_array& src)
{
	for(unsigned i = 0; i < cube_side::num_elements; ++i)
		set_data(static_cast<cube_side::type>(i), src[i]);
}

template<typename BitDepth>
typename sge::basic_cube_texture<BitDepth>::size_type
sge::basic_cube_texture<BitDepth>::size() const
{
	return border_size() * border_size();
}

template class sge::basic_cube_texture<sge::bit_depth16>;
template class sge::basic_cube_texture<sge::bit_depth32>;
