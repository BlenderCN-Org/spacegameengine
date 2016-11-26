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


#ifndef SGE_OPENGL_TEXTURE_FUNCS_SET_BOX_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FUNCS_SET_BOX_HPP_INCLUDED

#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/volume_config_fwd.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/dim3_fwd.hpp>
#include <sge/renderer/lock_box_fwd.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{
namespace funcs
{

void
set_box(
	sge::opengl::texture::binding const &,
	sge::opengl::context::object &,
	sge::opengl::texture::volume_config const &,
	sge::opengl::texture::buffer_type,
	sge::opengl::color_order,
	sge::opengl::color_base_type,
	sge::renderer::texture::mipmap::level,
	sge::renderer::dim3 const &,
	sge::renderer::lock_box const &,
	sge::renderer::const_raw_pointer src
);

}
}
}
}

#endif
