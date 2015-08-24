/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/color_buffer/optional_surface_ref.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/target/from_texture.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>


sge::renderer::target::offscreen_unique_ptr
sge::renderer::target::from_texture(
	sge::renderer::device::core &_device,
	sge::renderer::texture::planar &_texture
)
{
	if(
		!(
			_texture.capabilities()
			&
			sge::renderer::texture::capabilities::render_target
		)
	)
		throw
			sge::renderer::exception(
				FCPPT_TEXT("renderer::target_from_texture() called with a texture ")
				FCPPT_TEXT("that is not a render target!")
			);

	sge::renderer::target::offscreen_unique_ptr target(
		_device.create_target()
	);

	target->color_surface(
		sge::renderer::color_buffer::optional_surface_ref(
			_texture.level(
				sge::renderer::texture::mipmap::level(
					0u
				)
			)
		),
		sge::renderer::target::surface_index(
			0u
		)
	);

	target->viewport(
		sge::renderer::target::viewport(
			sge::renderer::pixel_rect(
				fcppt::math::vector::null<
					sge::renderer::pixel_rect::vector
				>(),
				fcppt::math::dim::structure_cast<
					sge::renderer::pixel_rect::dim,
					fcppt::cast::to_signed_fun
				>(
					fcppt::math::dim::structure_cast<
						sge::renderer::screen_size,
						fcppt::cast::size_fun
					>(
						_texture.size()
					)
				)
			)
		)
	);

	return
		target;
}
