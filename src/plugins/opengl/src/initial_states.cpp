/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../initial_states.hpp"
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/trampoline.hpp>

sge::renderer::state::list const
sge::opengl::initial_states()
{
	return
		sge::renderer::state::list
		(
			sge::renderer::state::source_blend_func::one
		)
		(
			sge::renderer::state::dest_blend_func::zero
		)
		(
			sge::renderer::state::stencil_func::off
		)
		(
			sge::renderer::state::alpha_func::off
		)
		(
			sge::renderer::state::int_::stencil_ref = 1
		)
		(
			sge::renderer::state::uint::stencil_mask = ~0u
		)
		(
			sge::renderer::state::float_::alpha_test_ref = 0.f
		);
}
