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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_render_state.hpp>
#include <sge/d3d9/state/parameters.hpp>
#include <sge/d3d9/state/set_render_state_bool.hpp>
#include <sge/d3d9/state/stencil_func.hpp>
#include <sge/d3d9/state/convert/stencil_func.hpp>
#include <sge/renderer/state/stencil_func.hpp>


void
sge::d3d9::state::stencil_func(
	state::parameters const &_parameters,
	sge::renderer::state::stencil_func::type const &_state
)
{
	bool const active(
		_state != sge::renderer::state::stencil_func::off
	);

	d3d9::state::set_render_state_bool(
		_parameters.device(),
		D3DRS_STENCILENABLE,
		active
	);

	if(
		active
	)
		d3d9::devicefuncs::set_render_state(
			_parameters.device(),
			D3DRS_STENCILFUNC,
			state::convert::stencil_func(
				_state
			)
		);
}
