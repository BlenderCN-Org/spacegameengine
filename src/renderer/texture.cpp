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
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>

sge::renderer::image_view const
sge::renderer::texture::lock(lock_flag_t const flags)
{
	return lock(rect(), flags);
}

sge::renderer::const_image_view const
sge::renderer::texture::lock() const
{
	return lock(rect());
}

sge::renderer::texture::rect_type const
sge::renderer::texture::rect() const
{
	return rect_type(
		rect_type::point_type(0,0),
		dim());
}

sge::renderer::texture::size_type
sge::renderer::texture::content() const
{
	return dim().content();
}

const sge::renderer::texture::dim_type
sge::renderer::gil_dim_to_sge(image_view::point_t const &d)
{
	return texture::dim_type(d.x, d.y);
}
