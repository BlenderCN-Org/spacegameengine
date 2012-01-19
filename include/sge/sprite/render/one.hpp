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


#ifndef SGE_SPRITE_RENDER_ONE_HPP_INCLUDED
#define SGE_SPRITE_RENDER_ONE_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/render/geometry_options.hpp>
#include <sge/sprite/render/matrix_options.hpp>
#include <sge/sprite/render/one_with_options.hpp>
#include <sge/sprite/render/options.hpp>
#include <sge/sprite/render/state_options.hpp>
#include <sge/sprite/render/vertex_options.hpp>
#include <sge/sprite/render/with_options.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename Choices,
	typename Buffers
>
void
one(
	sge::sprite::object<
		Choices
	> const &_sprite,
	Buffers &_buffers
)
{
	sge::sprite::render::one_with_options<
		sge::sprite::render::options<
			sge::sprite::render::geometry_options::fill,
			sge::sprite::render::matrix_options::set,
			sge::sprite::render::state_options::set,
			sge::sprite::render::vertex_options::declaration_and_buffer
		>
	>(
		_sprite,
		_buffers
	);
}

}
}
}

#endif
