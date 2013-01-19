/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/d3d9/state/convert/source_blend_func.hpp>
#include <sge/renderer/state/core/blend/source.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DBLEND
sge::d3d9::state::convert::source_blend_func(
	sge::renderer::state::core::blend::source const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::state::core::blend::source::zero:
		return D3DBLEND_ZERO;
	case sge::renderer::state::core::blend::source::one:
		return D3DBLEND_ONE;
	case sge::renderer::state::core::blend::source::dest_color:
		return D3DBLEND_DESTCOLOR;
	case sge::renderer::state::core::blend::source::inv_dest_color:
		return D3DBLEND_INVDESTCOLOR;
	case sge::renderer::state::core::blend::source::src_alpha:
		return D3DBLEND_SRCALPHA;
	case sge::renderer::state::core::blend::source::inv_src_alpha:
		return D3DBLEND_INVSRCALPHA;
	case sge::renderer::state::core::blend::source::dest_alpha:
		return D3DBLEND_DESTALPHA;
	case sge::renderer::state::core::blend::source::inv_dest_alpha:
		return D3DBLEND_INVDESTALPHA;
	case sge::renderer::state::core::blend::source::src_alpha_sat:
		return D3DBLEND_SRCALPHASAT;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
