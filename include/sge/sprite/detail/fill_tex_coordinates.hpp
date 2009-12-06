/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_FILL_TEX_COORDINATES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_TEX_COORDINATES_HPP_INCLUDED

#include <sge/sprite/detail/fill_tex_coordinates_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/texture/part.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Iterator,
	typename Choices,
	typename Elements
>
typename boost::enable_if<
	boost::mpl::contains<
		Elements,
		with_texture
	>,
	void
>::type
fill_tex_coordinates(
	Iterator const &iterator,
	object<
		Choices,
		Elements
	> const &sprite_
)
{
	if(
		!sprite_.texture()
		|| !sprite_.texture()->texture()
	)
		return;
	
	fill_tex_coordinates_impl(
		iterator,
		sprite_
	);
}

template<
	typename Iterator,
	typename Choices,
	typename Elements
>
typename boost::disable_if<
	boost::mpl::contains<
		Elements,
		with_texture
	>,
	void
>::type
fill_tex_coordinates(
	Iterator const &,
	object<
		Choices,
		Elements
	> const &
)
{
}

}
}
}

#endif
