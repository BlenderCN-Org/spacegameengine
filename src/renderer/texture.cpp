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


#include <sge/renderer/texture.hpp>
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/math/rect_impl.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>

void sge::renderer::texture::sub_data(
	const_image_view const &src,
	lock_rect const &dest)
{
	if(gil_dim_to_sge(src.dimensions()) != dest.dim())
		throw exception(
			SGE_TEXT("texture::sub_data: src's dim and dest's dim do not match!"));
	if(dest.right() > dim().w()
	|| dest.bottom() > dim().h())
		throw exception(
			SGE_TEXT("texture::sub_data: dest out of range!"));
	
	do_sub_data(
		src,
		dest);
}

sge::renderer::texture::size_type
sge::renderer::texture::size() const
{
	return dim().size();
}

const sge::renderer::texture::dim_type
sge::renderer::gil_dim_to_sge(image_view::point_t const &d)
{
	return texture::dim_type(d.x, d.y);
}
