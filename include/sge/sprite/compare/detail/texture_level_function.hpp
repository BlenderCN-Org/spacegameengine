/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_COMPARE_DETAIL_TEXTURE_LEVEL_FUNCTION_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_DETAIL_TEXTURE_LEVEL_FUNCTION_HPP_INCLUDED

#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/sprite/deref_texture.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/texture/part.hpp>


namespace sge
{
namespace sprite
{
namespace compare
{
namespace detail
{

template<
	template<
		typename
	> class Function,
	typename Level
>
struct texture_level_function
{
	typedef bool result_type;

	template<
		typename Choices
	>
	static
	result_type
	execute(
		sge::sprite::object<
			Choices
		> const &_left,
		sge::sprite::object<
			Choices
		> const &_right
	)
	{
		return
			Function<
				// TODO: Why is this a pointer?
				sge::renderer::texture::planar const *
			>()(
				&sge::sprite::deref_texture(
					_left. template texture_level<
						Level::value
					>()
				).texture(),
				&sge::sprite::deref_texture(
					_right. template texture_level<
						Level::value
					>()
				).texture()
			);
	}
};

}
}
}
}

#endif
