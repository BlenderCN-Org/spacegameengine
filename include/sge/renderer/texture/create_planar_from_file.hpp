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


#ifndef SGE_RENDERER_TEXTURE_CREATE_PLANAR_FROM_FILE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CREATE_PLANAR_FROM_FILE_HPP_INCLUDED

#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <sge/renderer/texture/address_mode2_fwd.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/image2d/file_fwd.hpp>

namespace sge
{
namespace renderer
{
namespace texture
{

SGE_RENDERER_SYMBOL
renderer::texture::planar_ptr const
create_planar_from_file(
	renderer::device &,
	image2d::file &,
	renderer::texture::mipmap::object const &,
	renderer::texture::address_mode2 const &,
	renderer::resource_flags_field const &
);

}
}
}

#endif
