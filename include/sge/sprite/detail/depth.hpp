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


#ifndef SGE_SPRITE_DETAIL_DEPTH_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_DEPTH_HPP_INCLUDED

#include <sge/sprite/with_depth.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/depth_type.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices
>
typename boost::enable_if<
	boost::mpl::contains<
		typename Choices::elements,
		with_depth
	>,
	typename depth_type<
		typename Choices::type_choices
	>::type
>::type
depth(
	object<
		Choices
	> const &sprite_
)
{
	return sprite_.z();
}

template<
	typename Choices
>
typename boost::disable_if<
	boost::mpl::contains<
		typename Choices::elements,
		with_depth
	>,
	typename depth_type<
		typename Choices::type_choices
	>::type
>::type
depth(
	object<
		Choices
	> const &
)
{
	return
		static_cast<
			typename depth_type<
				typename Choices::type_choices
			>::type
		>(0);
}

}
}
}

#endif
