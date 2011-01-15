/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/texture/part_raw.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/sub_data.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/box/basic_impl.hpp>

sge::texture::part_raw::part_raw(
	renderer::texture_ptr const _tex,
	renderer::lock_rect const &_area
)
:
	area_(_area),
	tex_(_tex)
{}

sge::texture::part_raw::part_raw(
	renderer::texture_ptr const _tex
)
:
	area_(
		renderer::lock_rect::vector::null(),
		_tex->dim()
	),
	tex_(_tex)
{}

sge::texture::part_raw::~part_raw()
{}

void
sge::texture::part_raw::data(
	image2d::view::const_object const &_src
)
{
	renderer::sub_data(
		tex_,
		_src,
		area().pos()
	);
}

sge::renderer::lock_rect const &
sge::texture::part_raw::area() const
{
	return area_;
}

sge::renderer::texture_ptr const
sge::texture::part_raw::texture()
{
	return tex_;
}

sge::renderer::const_texture_ptr const
sge::texture::part_raw::texture() const
{
	return tex_;
}

bool
sge::texture::part_raw::repeatable() const
{
	return area().dimension() == tex_->dim();
}
