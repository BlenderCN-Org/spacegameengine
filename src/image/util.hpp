/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_IMAGE_UTIL_HPP_INCLUDED
#define SGE_IMAGE_UTIL_HPP_INCLUDED

#include "../renderer/types.hpp"
#include "../renderer/renderer.hpp"
#include "../renderer/texture.hpp"
#include "./image_loader.hpp"

namespace sge
{

inline texture_ptr create_texture(renderer_ptr r, image_ptr p, unsigned mip_levels = 1, resource_flag_t flags = RF_Default)
{
	return r->create_texture(p->data(),p->width(),p->height(),mip_levels,flags);
}

inline texture_ptr create_texture(const std::string& path, renderer_ptr r, image_loader_ptr p, image::size_type w = 0, image::size_type h = 0, unsigned mip_levels = 1, resource_flag_t flags = RF_Default)
{
	return create_texture(r,p->load_image(path,w,h),mip_levels,flags);
}

}

#endif
