/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/devicefuncs/create_cube_texture.hpp>
#include <sge/d3d9/texture/d3d_cube_texture_unique_ptr.hpp>
#include <sge/d3d9/texture/mipmap/level_count.hpp>
#include <sge/d3d9/texture/mipmap/usage.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <fcppt/text.hpp>


sge::d3d9::texture::d3d_cube_texture_unique_ptr
sge::d3d9::devicefuncs::create_cube_texture(
	IDirect3DDevice9 &_device,
	sge::renderer::texture::cube_parameters const &_params,
	D3DFORMAT const _color_format,
	D3DPOOL const _pool,
	sge::d3d9::usage const _usage
)
{
	IDirect3DCubeTexture9 *ret = 0;

	if(
		_device.CreateCubeTexture(
			static_cast<
				UINT
			>(
				_params.size()
			),
			sge::d3d9::texture::mipmap::level_count(
				_params.mipmap()
			),
			_usage.get()
			|
			sge::d3d9::texture::mipmap::usage(
				_params.mipmap()
			).get(),
			_color_format,
			_pool,
			&ret,
			0
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("CreateTexture() failed!")
		);

	return
		sge::d3d9::texture::d3d_cube_texture_unique_ptr(
			ret
		);
}
