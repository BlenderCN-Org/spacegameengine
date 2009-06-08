/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_TEXTURE_FUNCTIONS_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_FUNCTIONS_HPP_INCLUDED

#include "d3dinclude.hpp"
#include <sge/renderer/texture.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/volume_texture.hpp>

namespace sge
{
namespace d3d9
{

IDirect3DTexture9 *
create_texture(
	d3d_device_ptr,
	rendereR::texture_dim const &dim,
	renderer::texture::filter const &filter,
	renderer::resource_flag_t flags,
	bool system_mem,
	bool render_target);

sge::texture::pointer lock_texture(
	d3d_texture_ptr,
	renderer::lock_rect const *rect,
	lock_flag_t lflags,
	resource_flag_t rflags);

void unlock_texture(
	d3d_texture_ptr);

void update_texture(
	d3d_device_ptr,
	IDirect3DBaseTexture9 *src,
	IDirect3DBaseTexture9 *dest);

/*
IDirect3DVolumeTexture9* create_volume_texture(
	d3d_device_ptr,
	const volume_texture::box_type& box,
	const filter_args& filter,
	resource_flag_t flags,
	bool system_mem);

sge::volume_texture::pointer
lock_volume_texture(
	d3d_volume_texture_ptr,
	const lock_box* box,
	lock_flag_t lflags,
	resource_flag_t rflags);

void unlock_volume_texture(
	d3d_volume_texture_ptr);
*/
}
}

#endif
