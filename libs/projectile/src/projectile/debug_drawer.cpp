/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/projectile/debug_drawer.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/projectile/impl/detail/debug_drawer_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/context_fwd.hpp>


sge::projectile::debug_drawer::debug_drawer(
	fcppt::log::context &_log,
	sge::projectile::world &_world,
	sge::renderer::device::core &_renderer
)
:
	impl_(
		fcppt::make_unique_ptr<
			sge::projectile::detail::debug_drawer_impl
		>(
			_log,
			_world,
			_renderer
		)
	)
{
}

void
sge::projectile::debug_drawer::update()
{
	impl_->update();
}

void
sge::projectile::debug_drawer::render(
	sge::renderer::context::core &_render_context
)
{
	impl_->render(
		_render_context
	);
}

void
sge::projectile::debug_drawer::active(
	bool const _active)
{
	impl_->active(
		_active
	);
}

bool
sge::projectile::debug_drawer::active() const
{
	return
		impl_->active();
}

sge::projectile::debug_drawer::~debug_drawer()
{
}
