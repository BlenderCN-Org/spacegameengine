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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_depth_stencil_surface.hpp>
#include <sge/d3d9/devicefuncs/set_render_target.hpp>
#include <sge/d3d9/surface/color.hpp>
#include <sge/d3d9/surface/depth_stencil.hpp>
#include <sge/d3d9/surface/optional_d3d_ref.hpp>
#include <sge/d3d9/target/basic_impl.hpp>
#include <sge/d3d9/target/offscreen.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/color_buffer/optional_surface_ref.hpp>
#include <sge/renderer/depth_stencil_buffer/optional_surface_ref.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/dynamic_optional_cast.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_int_range.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/index_map_impl.hpp>


sge::d3d9::target::offscreen::offscreen(
	IDirect3DDevice9 &_device,
	sge::renderer::caps::target_surface_indices const _max_surfaces
)
:
	base(
		_device,
		sge::renderer::target::viewport(
			sge::renderer::pixel_rect::null()
		),
		_max_surfaces
	),
	color_surfaces_(),
	depth_stencil_surface_()
{
}

sge::d3d9::target::offscreen::~offscreen()
{
}

void
sge::d3d9::target::offscreen::color_surface(
	sge::renderer::color_buffer::optional_surface_ref const &_surface,
	sge::renderer::target::surface_index const _index
)
{
	color_surfaces_[
		_index.get()
	] =
		fcppt::dynamic_optional_cast<
			sge::d3d9::surface::color &
		>(
			_surface
		);
}

void
sge::d3d9::target::offscreen::depth_stencil_surface(
	sge::renderer::depth_stencil_buffer::optional_surface_ref const &_surface
)
{
	depth_stencil_surface_ =
		fcppt::dynamic_optional_cast<
			sge::d3d9::surface::depth_stencil &
		>(
			_surface
		);
}

bool
sge::d3d9::target::offscreen::needs_present() const
{
	return
		false;
}

void
sge::d3d9::target::offscreen::on_activate()
{
	this->change_surfaces(
		true
	);
}

void
sge::d3d9::target::offscreen::on_deactivate()
{
	this->change_surfaces(
		false
	);
}

void
sge::d3d9::target::offscreen::change_surfaces(
	bool const _activate
)
{
	for(
		// Don't deactivate the 0th color surface because D3D9 doesn't allow it
		sge::d3d9::target::offscreen::color_surface_map::size_type const index
		:
		fcppt::make_int_range(
			_activate
			?
				fcppt::literal<
					sge::d3d9::target::offscreen::color_surface_map::size_type
				>(
					0u
				)
			:
				fcppt::literal<
					sge::d3d9::target::offscreen::color_surface_map::size_type
				>(
					1u
				)
			,
			color_surfaces_.size()
		)
	)
		fcppt::maybe_void(
			color_surfaces_[
				index
			],
			[
				_activate,
				index,
				this
			](
				sge::d3d9::surface::color &_surface
			)
			{
				sge::d3d9::devicefuncs::set_render_target(
					this->device(),
					fcppt::strong_typedef_construct_cast<
						sge::renderer::target::surface_index,
						fcppt::cast::size_fun
					>(
						index
					),
					_activate
					?
						sge::d3d9::surface::optional_d3d_ref(
							_surface.surface()
						)
					:
						sge::d3d9::surface::optional_d3d_ref()
				);
			}
		);

	fcppt::maybe_void(
		depth_stencil_surface_,
		[
			_activate,
			this
		](
			sge::d3d9::surface::depth_stencil &_surface
		)
		{
			sge::d3d9::devicefuncs::set_depth_stencil_surface(
				this->device(),
				_activate
				?
					sge::d3d9::surface::optional_d3d_ref(
						_surface.surface()
					)
				:
					sge::d3d9::surface::optional_d3d_ref()
			);
		}
	);
}

template
class
sge::d3d9::target::basic<
	sge::renderer::target::offscreen
>;
