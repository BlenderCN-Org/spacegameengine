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


#ifndef SGE_D3D9_TEXTURE_ADDRESS_MODE_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_ADDRESS_MODE_HPP_INCLUDED

#include "../d3dinclude.hpp"
#include "../state/address_mode_fwd.hpp"
#include <sge/renderer/stage.hpp>
#include <sge/renderer/texture/address_mode2_fwd.hpp>
#include <sge/renderer/texture/address_mode3_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

void
address_mode(
	IDirect3DDevice9 *const _device,
	state::address_mode &_state,
	renderer::stage const _stage,
	renderer::texture::address_mode2 const &
);

void
address_mode(
	IDirect3DDevice9 *const _device,
	state::address_mode &_state,
	renderer::stage const _stage,
	renderer::texture::address_mode3 const &
);

}
}
}

#endif
