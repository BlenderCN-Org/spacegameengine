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


#include "../get_depth_stencil_surface.hpp"
#include "../../d3dinclude.hpp"
#include "../../surface/d3d_unique_ptr.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::d3d9::surface::d3d_unique_ptr
sge::d3d9::devicefuncs::get_depth_stencil_surface(
	IDirect3DDevice9 *const _device
)
{
	IDirect3DSurface9 *ret;

	switch(
		_device->GetDepthStencilSurface(
			&ret
		)
	)
	{
	case D3D_OK:
		return
			d3d9::surface::d3d_unique_ptr(
				ret
			);
	case D3DERR_NOTFOUND:
		return d3d9::surface::d3d_unique_ptr();
	}
	
	throw sge::renderer::exception(
		FCPPT_TEXT("GetDepthStencilSurface() failed!")
	);
}
