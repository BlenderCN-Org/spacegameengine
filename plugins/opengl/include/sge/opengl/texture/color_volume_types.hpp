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


#ifndef SGE_OPENGL_TEXTURE_COLOR_VOLUME_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_COLOR_VOLUME_TYPES_HPP_INCLUDED

#include <sge/opengl/texture/basic_lockable_buffer_fwd.hpp>
#include <sge/opengl/texture/buffer_volume_types_fwd.hpp>
#include <sge/opengl/texture/color_format_types_fwd.hpp>
#include <sge/opengl/texture/color_volume_types_fwd.hpp>
#include <sge/renderer/color_buffer/writable_volume_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

struct color_volume_types
{
	typedef
	sge::renderer::color_buffer::writable_volume
	base;

	// TODO: Factor this out!
	typedef
	sge::opengl::texture::basic_lockable_buffer<
		sge::opengl::texture::color_volume_types
	>
	gl_buffer;

	typedef
	sge::opengl::texture::buffer_volume_types
	dim_types;

	typedef
	sge::opengl::texture::color_format_types
	format_types;
};

}
}
}

#endif
