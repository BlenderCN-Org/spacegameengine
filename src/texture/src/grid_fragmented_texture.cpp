/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007       Simon Stienen (s.stienen@slashlife.org)

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

#include "../grid_fragmented_texture.hpp"
#include "../atlasing.hpp"
#include "../../math/utility.hpp"
#include "../../math/rect_impl.hpp"

#define MAX_TEX_SIZE 4096

namespace {
	inline void find_texture_size(
		sge::texture::size_type &sizeref,
		sge::texture::size_type  maxsize,
		sge::texture::size_type  partsize
	) {
		const sge::texture::size_type halfpart = partsize / 2;
		sge::texture::size_type tex_t_size = sizeref, remainder = tex_t_size % partsize;
		while ((tex_t_size < maxsize) && remainder > halfpart)
			remainder = (tex_t_size *= 2);
		if (remainder <= halfpart)
			sizeref = tex_t_size;
		if ((sizeref < MAX_TEX_SIZE) && (((2*sizeref) % partsize) <= remainder)) // better or equally good
			sizeref *= 2;
	}
}

sge::grid_fragmented_texture::grid_fragmented_texture(renderer_ptr rend, texture::size_type width, texture::size_type height, const filter_args& filter, texture::size_type mintexsize)
: rend(rend)
, my_filter(my_filter)
, part_width(width)
, part_height(height)
{
	tex_x_size = tex_y_size = math::next_pow_2(mintexsize);
	if (tex_x_size < part_width ) tex_x_size = math::next_pow_2(part_width );
	if (tex_y_size < part_height) tex_y_size = math::next_pow_2(part_height);
	find_texture_size(tex_x_size, MAX_TEX_SIZE, part_width );
	find_texture_size(tex_y_size, MAX_TEX_SIZE, part_height);
	parts_per_row = tex_x_size / part_width;
	parts_free = parts_total = parts_per_row * (tex_y_size / part_height);
	reserved = new char[parts_total];
	try {
		for(unsigned i=0; i<parts_total; i++) reserved[i] = false;
	} catch(...) {
		delete[] reserved;
		throw;
	}
}

sge::grid_fragmented_texture::grid_fragmented_texture(const grid_fragmented_texture &other)
: rend(other.rend)
, my_filter(other.my_filter)
, part_width(other.part_width)
, part_height(other.part_height)
, tex_x_size(other.tex_x_size)
, tex_y_size(other.tex_y_size)
, parts_per_row(other.parts_per_row)
, parts_total(other.parts_total)
, parts_free(other.parts_total) {
	reserved = new char[parts_total];
	for(unsigned i=0; i<parts_total; i++) reserved[i] = false;
}

sge::grid_fragmented_texture::~grid_fragmented_texture() {
	delete[] reserved;
}

sge::virtual_texture_ptr sge::grid_fragmented_texture::consume_fragments(const texture::size_type w, const texture::size_type h)
{
	if (!parts_free)
		return sge::virtual_texture_ptr();

	if ((w > part_width) || (h > part_height))
		; // TODO: Error handling (throw exception?)
	texture::size_type
		next_w = math::next_pow_2(w),
		next_h = math::next_pow_2(h);

	if (!tex)
		tex = rend->create_texture(0, tex_x_size, tex_y_size, my_filter);

	const bool no_atlasing = math::is_int_log2(w) && math::is_int_log2(h);

	texture::size_type x, y;
	{ unsigned index = 0; while (reserved[index]) ++index;
		reserved[index] = true;
		x = (index % parts_per_row) * part_width;
		y = (index / parts_per_row) * part_height;
	}

	virtual_texture_ptr vr(new virtual_texture(
		lock_rect(lock_rect::point_type(0,0), no_atlasing ? lock_rect::dim_type(w,h) : atlased_size(w,h)), *this, no_atlasing));
	--parts_free;
	return vr;
}

void sge::grid_fragmented_texture::return_fragments(const virtual_texture &t)
{
	unsigned index =
		(t.area().left() / part_width) +
		(t.area().top() / part_height) * parts_per_row;
	reserved[index] = false;
	if (parts_total == ++parts_free)
		tex.reset();
}

sge::texture_ptr sge::grid_fragmented_texture::get_texture() const
{
	return tex;
}

bool sge::grid_fragmented_texture::repeatable() const
{
	return true;
}

sge::fragmented_texture* sge::grid_fragmented_texture::clone() const
{
	return new grid_fragmented_texture(*this);
}
