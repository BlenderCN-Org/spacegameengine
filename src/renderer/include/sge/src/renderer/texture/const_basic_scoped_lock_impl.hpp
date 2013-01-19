/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_RENDERER_TEXTURE_CONST_BASIC_SCOPED_LOCK_IMPL_HPP_INCLUDED
#define SGE_SRC_RENDERER_TEXTURE_CONST_BASIC_SCOPED_LOCK_IMPL_HPP_INCLUDED

#include <sge/image/view/const_object.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/basic_lock_box.hpp>
#include <sge/renderer/texture/const_basic_scoped_lock.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>


template<
	typename Texture
>
sge::renderer::texture::const_basic_scoped_lock<
	Texture
>::const_basic_scoped_lock(
	Texture const &_texture
)
:
	lock_(
		_texture.level(
			sge::renderer::texture::mipmap::level(
				0u
			)
		)
	)
{
}

template<
	typename Texture
>
sge::renderer::texture::const_basic_scoped_lock<
	Texture
>::const_basic_scoped_lock(
	Texture const &_texture,
	lock_area const &_area
)
:
	lock_(
		_texture.level(
			sge::renderer::texture::mipmap::level(
				0u
			)
		),
		_area
	)
{
}

template<
	typename Texture
>
typename sge::renderer::texture::const_basic_scoped_lock<
	Texture
>::const_view const
sge::renderer::texture::const_basic_scoped_lock<
	Texture
>::value() const
{
	return
		lock_.value();
}

template<
	typename Texture
>
sge::renderer::texture::const_basic_scoped_lock<
	Texture
>::~const_basic_scoped_lock()
{
}

#endif
