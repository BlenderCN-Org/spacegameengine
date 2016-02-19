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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/dest_blend_func.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DBLEND
sge::d3d9::state::convert::dest_blend_func(
	sge::renderer::state::core::blend::dest const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::state::core::blend::dest::zero:
		return D3DBLEND_ZERO;
	case sge::renderer::state::core::blend::dest::one:
		return D3DBLEND_ONE;
	case sge::renderer::state::core::blend::dest::src_color:
		return D3DBLEND_SRCCOLOR;
	case sge::renderer::state::core::blend::dest::inv_src_color:
		return D3DBLEND_INVSRCCOLOR;
	case sge::renderer::state::core::blend::dest::src_alpha:
		return D3DBLEND_SRCALPHA;
	case sge::renderer::state::core::blend::dest::inv_src_alpha:
		return D3DBLEND_INVSRCALPHA;
	case sge::renderer::state::core::blend::dest::dest_alpha:
		return D3DBLEND_DESTALPHA;
	case sge::renderer::state::core::blend::dest::inv_dest_alpha:
		return D3DBLEND_INVDESTALPHA;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
