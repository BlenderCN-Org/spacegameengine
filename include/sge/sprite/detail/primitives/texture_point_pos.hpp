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


#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_POINT_POS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_POINT_POS_HPP_INCLUDED

#include <sge/sprite/types/texture_point_pos.hpp>
#include <sge/sprite/config/custom_texture_point_pos_fwd.hpp>
#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/roles/texture_point_pos.hpp>
#include <majutsu/role.hpp>
#include <majutsu/simple.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace primitives
{

template<
	typename Choices,
	typename Levels,
	typename PointPos
>
struct texture_point_pos;

template<
	typename Choices,
	typename Levels
>
struct texture_point_pos<
	Choices,
	Levels,
	sge::sprite::config::custom_texture_point_pos<
		false
	>
>
{
	typedef boost::mpl::vector0<> type;
};

template<
	typename Choices,
	typename Levels
>
struct texture_point_pos<
	Choices,
	Levels,
	sge::sprite::config::custom_texture_point_pos<
		true
	>
>
{
private:
	template<
		typename Level
	>
	struct make_role
	{
		typedef majutsu::role<
			majutsu::simple<
				typename sge::sprite::types::texture_point_pos<
					typename Choices::type_choices
				>::type
			>,
			sge::sprite::roles::texture_point_pos<
				Level::value
			>
		> type;
	};
public:
	typedef typename sge::sprite::detail::transform_texture_levels_static<
		make_role<
			boost::mpl::_1
		>,
		Levels
	>::type type;
};

}
}
}
}

#endif
