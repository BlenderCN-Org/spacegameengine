/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/d3d9/state/convert/stencil_func.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DCMPFUNC
sge::d3d9::state::convert::stencil_func(
	sge::renderer::state::stencil_func::type const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::state::stencil_func::off:
		break;
	case sge::renderer::state::stencil_func::never:
		return D3DCMP_NEVER;
	case sge::renderer::state::stencil_func::less:
		return D3DCMP_LESS;
	case sge::renderer::state::stencil_func::equal:
		return D3DCMP_EQUAL;
	case sge::renderer::state::stencil_func::less_equal:
		return D3DCMP_LESSEQUAL;
	case sge::renderer::state::stencil_func::greater:
		return D3DCMP_GREATER;
	case sge::renderer::state::stencil_func::not_equal:
		return D3DCMP_NOTEQUAL;
	case sge::renderer::state::stencil_func::greater_equal:
		return D3DCMP_GREATEREQUAL;
	case sge::renderer::state::stencil_func::always:
		return D3DCMP_ALWAYS;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
