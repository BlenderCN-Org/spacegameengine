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
#include <sge/d3d9/state/convert/address_mode.hpp>
#include <sge/renderer/state/core/sampler/address/mode.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DTEXTUREADDRESS
sge::d3d9::state::convert::address_mode(
	sge::renderer::state::core::sampler::address::mode::type const _mode
)
{
	switch(
		_mode
	)
	{
	case sge::renderer::state::core::sampler::address::mode::clamp:
		return D3DTADDRESS_CLAMP;
	case sge::renderer::state::core::sampler::address::mode::mirror_repeat:
		return D3DTADDRESS_MIRROR;
	case sge::renderer::state::core::sampler::address::mode::repeat:
		return D3DTADDRESS_WRAP;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
