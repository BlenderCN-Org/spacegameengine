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


#ifndef SGE_SPRITE_DETAIL_SET_TEXTURES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_SET_TEXTURES_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/detail/apply_texture_levels.hpp>
#include <sge/sprite/detail/set_texture_level.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename TextureLevels,
	typename Choices
>
typename boost::enable_if<
	boost::mpl::contains<
		typename Choices::elements,
		sprite::with_texture
	>,
	void
>::type
set_textures(
	sprite::object<
		Choices
	> const &_obj,
	sge::renderer::device &_rend
)
{
	detail::apply_texture_levels<
		TextureLevels
	>(
		detail::set_texture_level<
			Choices
		>(
			_obj,
			_rend
		)
	);
}

template<
	typename TextureLevels,
	typename Choices
>
typename boost::disable_if<
	boost::mpl::contains<
		typename Choices::elements,
		sprite::with_texture
	>,
	void
>::type
set_textures(
	sprite::object<
		Choices
	> const &,
	sge::renderer::device &
)
{
}

}
}
}

#endif
