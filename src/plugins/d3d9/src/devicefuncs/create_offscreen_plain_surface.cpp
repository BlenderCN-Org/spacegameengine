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
#include <sge/d3d9/convert/color_format.hpp>
#include <sge/d3d9/devicefuncs/create_offscreen_plain_surface.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


sge::d3d9::surface::d3d_unique_ptr
sge::d3d9::devicefuncs::create_offscreen_plain_surface(
	IDirect3DDevice9 &_device,
	sge::renderer::dim2 const &_dim,
	sge::image::color::format const _format,
	D3DPOOL const _pool
)
{
	IDirect3DSurface9 *ret;

	if(
		_device.CreateOffscreenPlainSurface(
			static_cast<
				UINT
			>(
				_dim.w()
			),
			static_cast<
				UINT
			>(
				_dim.h()
			),
			sge::d3d9::convert::color_format(
				_format
			),
			_pool,
			&ret,
			0
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("CreateOffscreenPlainSurface() failed!")
		);

	return
		sge::d3d9::surface::d3d_unique_ptr(
			ret
		);
}
