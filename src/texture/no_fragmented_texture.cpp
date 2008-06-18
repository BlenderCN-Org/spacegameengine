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


#include <sge/texture/no_fragmented_texture.hpp>
#include <sge/texture/atlasing.hpp>
#include <sge/iostream.hpp>
#include <sge/math/power.hpp>
#include <ostream>

sge::no_fragmented_texture::no_fragmented_texture(
	const renderer::device_ptr rend,
	const renderer::filter_args& my_filter)
 : rend(rend),
   my_filter(my_filter)
{}

const sge::virtual_texture_ptr
sge::no_fragmented_texture::consume_fragments(
	const renderer::texture::dim_type& dim)
{
	if(tex)
		return virtual_texture_ptr();

	const renderer::texture::dim_type real_dim(atlased_bounds(dim));

	// FIXME: boost::gil!
   	//tex = rend->create_texture(0, real_dim, my_filter);

	if(real_dim != dim)
		sge::cerr << SGE_TEXT("warning: You used a no_fragmented_texture whose dimensions are not a power of 2.")\
		             SGE_TEXT(" This is slower to load and requires more texture memory because it needs atlasing and thus is not intuitive.")\
			     SGE_TEXT(" The texture's size was ") << dim << SGE_TEXT(".\n");

	return virtual_texture_ptr(
		new virtual_texture(
			renderer::lock_rect(
				renderer::lock_rect::point_type(0,0),
				atlased_size(dim)),
			*this,
			need_atlasing(dim.w()),
			need_atlasing(dim.h())));
}

void sge::no_fragmented_texture::return_fragments(const virtual_texture&)
{
	tex.reset();
}

const sge::renderer::texture_ptr
sge::no_fragmented_texture::get_texture() const
{
	return tex;
}

bool sge::no_fragmented_texture::repeatable() const
{
	return true;
}
