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
#include <sge/d3d9/convert/bool.hpp>
#include <sge/d3d9/devicefuncs/set_sampler_state.hpp>
#include <sge/d3d9/devicefuncs/set_texture.hpp>
#include <sge/d3d9/texture/base.hpp>
#include <sge/d3d9/texture/set.hpp>
#include <sge/image/color/format_is_srgb.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>


void
sge::d3d9::texture::set(
	IDirect3DDevice9 &_device,
	sge::renderer::texture::stage const _stage,
	sge::renderer::texture::const_optional_base_ref const &_base
)
{
	sge::d3d9::devicefuncs::set_texture(
		_device,
		_stage,
		_base
	);

	if(
		_base
	)
		sge::d3d9::devicefuncs::set_sampler_state(
			_device,
			_stage,
			D3DSAMP_SRGBTEXTURE,
			static_cast<
				DWORD
			>(
				sge::d3d9::convert::bool_(
					sge::image::color::format_is_srgb(
						dynamic_cast<
							sge::d3d9::texture::base const &
						>(
							*_base
						).color_format()
					)
				)
			)
		);
}
