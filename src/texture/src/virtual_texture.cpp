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

#include "../virtual_texture.hpp"
#include "../fragmented_texture.hpp"

sge::virtual_texture::virtual_texture(const lock_rect& _area, fragmented_texture* const fragment, const bool _repeatable)
 : _area(_area),
   fragment(fragment),
   _repeatable(_repeatable)
{}

sge::virtual_texture::~virtual_texture()
{
	fragment->return_fragments(*this);
}

sge::lock_rect sge::virtual_texture::area() const
{
	return _area;
}

sge::texture_ptr sge::virtual_texture::my_texture() const
{
	return fragment->get_texture();
}

bool sge::virtual_texture::repeatable() const
{
	return _repeatable;
}

void sge::virtual_texture::set_data(const texture::const_pointer src)
{
	my_texture()->set_data(src,&_area);
}

