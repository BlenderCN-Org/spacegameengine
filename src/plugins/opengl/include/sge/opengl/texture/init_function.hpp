/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_TEXTURE_INIT_FUNCTION_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_INIT_FUNCTION_HPP_INCLUDED

#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/renderer/basic_dim_fwd.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/math/size_type.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	fcppt::math::size_type Size
>
struct init_function
{
	typedef
	void
	(*type)
	(
		sge::opengl::texture::binding const &,
		sge::opengl::context::system::object &,
		sge::opengl::texture::buffer_type,
		sge::opengl::color_format,
		sge::opengl::color_format_type,
		sge::opengl::internal_color_format,
		sge::renderer::texture::mipmap::level,
		typename sge::renderer::basic_dim<
			Size
		>::type const &,
		sge::renderer::const_raw_pointer
	);
};

}
}
}

#endif
