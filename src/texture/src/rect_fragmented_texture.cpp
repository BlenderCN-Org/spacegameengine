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


#include "../rect_fragmented_texture.hpp"

sge::rect_fragmented_texture::rect_fragmented_texture(const renderer_ptr rend)
: rend(rend),
  cur_x(0),
  cur_y(0),
  cur_height(0)
{}

sge::virtual_texture_ptr sge::rect_fragmented_texture::consume_fragments(const texture::size_type w, const texture::size_type h)
{
	if(!tex)
		tex = rend->create_texture(0, rend->caps().max_tex_size, rend->caps().max_tex_size, linear_filter);

	// if there is no space left for the requested height
	if(cur_y + h >= tex->height())
		return virtual_texture_ptr();

	// if the current line is full advance to the next
	if(cur_x + w >= tex->width())
	{
		cur_x = 0;
		cur_y += cur_height + 1;
		cur_height = 0;
	}

	if(cur_y + h>= tex->height())
		return virtual_texture_ptr();

	const virtual_texture_ptr ret(new virtual_texture(lock_rect(lock_rect::point_type(cur_x, cur_y), lock_rect::dim_type(w, h)), this));

	cur_x += w;
	cur_height = std::max(cur_height, h);

	return ret;
}

void sge::rect_fragmented_texture::return_fragments(const virtual_texture&)
{
	// FIXME
}

sge::texture_ptr sge::rect_fragmented_texture::get_texture() const
{
	return tex;
}

sge::fragmented_texture* sge::rect_fragmented_texture::clone() const
{
	return new rect_fragmented_texture(rend);
}
