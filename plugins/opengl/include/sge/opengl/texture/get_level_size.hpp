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


#ifndef SGE_OPENGL_TEXTURE_GET_LEVEL_SIZE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_GET_LEVEL_SIZE_HPP_INCLUDED

#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/renderer/basic_dim_fwd.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	fcppt::math::size_type Size
>
sge::renderer::basic_dim<
	Size
>
get_level_size(
	sge::opengl::texture::binding const &,
	sge::opengl::texture::buffer_type,
	sge::renderer::texture::mipmap::level
);

}
}
}

#define SGE_OPENGL_TEXTURE_DECLARE_GET_LEVEL_SIZE(\
	seq,\
	_,\
	dimension\
)\
extern \
template \
sge::renderer::basic_dim<\
	dimension\
> \
sge::opengl::texture::get_level_size<\
	dimension\
>(\
	sge::opengl::texture::binding const &,\
	sge::opengl::texture::buffer_type,\
	sge::renderer::texture::mipmap::level\
);

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_TEXTURE_DECLARE_GET_LEVEL_SIZE,
	_,
	SGE_OPENGL_TEXTURE_PP_DIMS
)

#endif
