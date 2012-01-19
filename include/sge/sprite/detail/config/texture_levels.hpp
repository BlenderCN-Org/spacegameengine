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


#ifndef SGE_SPRITE_DETAIL_CONFIG_TEXTURE_LEVELS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_TEXTURE_LEVELS_HPP_INCLUDED

#include <sge/sprite/config/is_with_texture.hpp>
#include <sge/sprite/config/is_with_texture_point_size.hpp>
#include <sge/sprite/detail/config/find_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace config
{

template<
	typename Choices
>
struct texture_levels
{
	typedef typename
	sge::sprite::detail::config::find_if<
		typename Choices::optional_elements,
		sge::sprite::config::is_with_texture
	>::type with_texture_iterator;

	typedef typename
	sge::sprite::detail::config::find_if<
		typename Choices::optional_elements,
		sge::sprite::config::is_with_texture_point_size
	>::type with_texture_point_size_iterator;

	typedef typename boost::mpl::deref<
		typename boost::mpl::if_<
			boost::is_same<
				with_texture_iterator,
				typename boost::mpl::end<
					typename Choices::optional_elements
				>::type
			>,
			with_texture_point_size_iterator,
			with_texture_iterator
		>::type
	>::type::texture_levels type;
};

}
}
}
}

#endif
