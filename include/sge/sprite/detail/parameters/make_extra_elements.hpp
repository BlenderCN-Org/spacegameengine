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


#ifndef SGE_SPRITE_DETAIL_PARAMETERS_MAKE_EXTRA_ELEMENTS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PARAMETERS_MAKE_EXTRA_ELEMENTS_HPP_INCLUDED

#include <sge/sprite/detail/config/needs_use_center.hpp>
#include <sge/sprite/detail/config/needs_use_texture_size.hpp>
#include <sge/sprite/detail/roles/use_center.hpp>
#include <sge/sprite/detail/roles/use_texture_size.hpp>
#include <majutsu/fundamental.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace parameters
{

template<
	typename Choices
>
using make_extra_elements
=
typename
boost::mpl::fold<
	boost::mpl::vector2<
		boost::mpl::pair<
			sge::sprite::detail::config::needs_use_center<
				Choices
			>,
			majutsu::role<
				majutsu::fundamental<
					bool
				>,
				sge::sprite::detail::roles::use_center
			>
		>,
		boost::mpl::pair<
			sge::sprite::detail::config::needs_use_texture_size<
				Choices
			>,
			majutsu::role<
				majutsu::fundamental<
					bool
				>,
				sge::sprite::detail::roles::use_texture_size
			>
		>
	>,
	boost::mpl::vector0<>,
	boost::mpl::if_<
		boost::mpl::first<
			boost::mpl::_2
		>,
		boost::mpl::push_back<
			boost::mpl::_1,
			boost::mpl::second<
				boost::mpl::_2
			>
		>,
		boost::mpl::_1
	>
>::type;

}
}
}
}

#endif
