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


#include <sge/opengl/texture/instantiate_dim.hpp>
#include <sge/opengl/texture/mipmap/all_levels.hpp>
#include <sge/opengl/texture/mipmap/auto_generate.hpp>
#include <sge/opengl/texture/mipmap/generate_levels.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/texture/mipmap/all_levels_rep.hpp>
#include <sge/renderer/texture/mipmap/auto_generate.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


template<
	fcppt::math::size_type Size
>
void
sge::opengl::texture::mipmap::all_levels(
	sge::opengl::texture::mipmap::parameters<
		Size
	> const &_parameters,
	sge::renderer::texture::mipmap::all_levels_rep const &_rep
)
{
	if(
		_rep.auto_generate()
		==
		sge::renderer::texture::mipmap::auto_generate::yes
	)
		sge::opengl::texture::mipmap::auto_generate(
			_parameters.binding(),
			_parameters.system_context(),
			_parameters.type()
		);
	else
		sge::opengl::texture::mipmap::generate_levels(
			_parameters,
			sge::renderer::texture::mipmap::level_count(
				std::numeric_limits<
					sge::renderer::texture::mipmap::level_count::value_type
				>::max()
			)
		);
}

#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_ALL_LEVELS(\
	dimension\
)\
template \
void \
sge::opengl::texture::mipmap::all_levels<\
	dimension\
>(\
	sge::opengl::texture::mipmap::parameters<\
		dimension\
	> const &,\
	sge::renderer::texture::mipmap::all_levels_rep const &\
);

SGE_OPENGL_TEXTURE_INSTANTIATE_DIM(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_ALL_LEVELS
)
