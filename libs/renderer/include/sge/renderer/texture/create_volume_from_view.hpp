/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_TEXTURE_CREATE_VOLUME_FROM_VIEW_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CREATE_VOLUME_FROM_VIEW_HPP_INCLUDED

#include <sge/image3d/view/const_object_fwd.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb_fwd.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::texture::volume_unique_ptr
create_volume_from_view(
	sge::renderer::device::core &,
	sge::image3d::view::const_object const &,
	sge::renderer::texture::mipmap::object const &,
	sge::renderer::resource_flags_field const &,
	sge::renderer::texture::emulate_srgb
);

}
}
}

#endif
