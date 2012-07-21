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
#include <sge/d3d9/parameters/convert/depth_stencil_buffer.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DFORMAT
sge::d3d9::parameters::convert::depth_stencil_buffer(
	sge::renderer::pixel_format::depth_stencil::type const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::pixel_format::depth_stencil::off:
		return D3DFMT_UNKNOWN;
	case sge::renderer::pixel_format::depth_stencil::d16:
		return D3DFMT_D16;
	case sge::renderer::pixel_format::depth_stencil::d24:
		return D3DFMT_D24X8;
	case sge::renderer::pixel_format::depth_stencil::d32:
		return D3DFMT_D32;
	case sge::renderer::pixel_format::depth_stencil::d24s8:
		return D3DFMT_D24S8;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
