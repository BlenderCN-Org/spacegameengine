/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/pos.hpp>
#include <sge/texture/sub_data.hpp>
#include <sge/texture/atlasing/border_h.hpp>
#include <sge/texture/atlasing/inner_rect.hpp>


void
sge::texture::atlasing::border_h(
	sge::renderer::texture::planar &_texture,
	sge::image2d::view::const_object const &_source,
	sge::texture::atlasing::inner_rect const &_inner_area
)
{
	sge::renderer::dim2 const dim(
		sge::image2d::view::size(
			_source
		)
	);

	sge::texture::sub_data(
		_texture,
		sge::image2d::view::sub(
			_source,
			sge::renderer::lock_rect(
				sge::renderer::lock_rect::vector::null(),
				sge::renderer::lock_rect::dim(
					dim.w(),
					1u
				)
			)
		),
		sge::texture::pos(
			_inner_area.get().left(),
			_inner_area.get().top() - 1u
		)
	);

	sge::texture::sub_data(
		_texture,
		sge::image2d::view::sub(
			_source,
			sge::renderer::lock_rect(
				sge::renderer::lock_rect::vector(
					0u,
					dim.h() - 1u
				),
				sge::renderer::lock_rect::dim(
					dim.w(),
					1u
				)
			)
		),
		sge::texture::pos(
			_inner_area.get().left(),
			_inner_area.get().bottom() + 1u
		)
	);
}
