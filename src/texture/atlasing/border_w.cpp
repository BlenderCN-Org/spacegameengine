/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/texture/atlasing/border_w.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/sub_data.hpp>
#include <sge/image2d/view/dim.hpp>
#include <sge/image2d/view/sub.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/variant/object_impl.hpp>

void
sge::texture::atlasing::border_w(
	renderer::texture_ptr const tex,
	image2d::view::const_object const &src,
	renderer::lock_rect const &outer_area,
	renderer::lock_rect const &inner_area
)
{
	renderer::dim2 const dim(
		image2d::view::dim(
			src
		)
	);

	renderer::sub_data(
		tex,
		image2d::view::sub(
			src,
			renderer::lock_rect(
				renderer::lock_rect::vector::null(),
				renderer::lock_rect::dim(
					1,
					dim.h()
				)
			)
		),
		renderer::texture_pos_type(
			outer_area.left(),
			inner_area.top()
		)
	);

	if(inner_area.right() + 1 == outer_area.right())
		return;

	renderer::sub_data(
		tex,
		image2d::view::sub(
			src,
			renderer::lock_rect(
				renderer::lock_rect::vector(
					dim.w() - 1,
					0
				),
				renderer::lock_rect::dim(
					1,
					dim.h()
				)
			)
		),
		renderer::texture_pos_type(
			outer_area.right() - 1,
			inner_area.top()
		)
	);
}
