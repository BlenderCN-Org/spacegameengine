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


#ifndef SGE_PARSE_JSON_DETAIL_IS_ARRAY_HPP_INCLUDED
#define SGE_PARSE_JSON_DETAIL_IS_ARRAY_HPP_INCLUDED

#include <fcppt/container/array.hpp>
#include <fcppt/tr1/array.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/detail/static_storage.hpp>
#include <fcppt/math/dim/static.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/array.hpp>
#include <cstddef>

namespace sge
{
namespace parse
{
namespace json
{
namespace detail
{
template<typename T>
struct is_array : boost::false_type {};

template<typename T,std::size_t N>
struct is_array< fcppt::container::array<T,N> > : boost::true_type {};

template<typename T,std::size_t N>
struct is_array< std::tr1::array<T,N> > : boost::true_type {};

template<typename T,std::size_t N>
struct is_array< boost::array<T,N> > : boost::true_type {};

template<typename T,fcppt::math::size_type N>
struct is_array
<
	fcppt::math::vector::basic
	<
		T,
		boost::mpl::integral_c
		<
			fcppt::math::size_type,
			N
		>,
		typename
		fcppt::math::detail::static_storage
		<
			T,
			N
		>::type
	>
> : boost::true_type {};

template<typename T,fcppt::math::size_type N>
struct is_array
<
	fcppt::math::dim::basic
	<
		T,
		boost::mpl::integral_c
		<
			fcppt::math::size_type,
			N
		>,
		typename
		fcppt::math::detail::static_storage
		<
			T,
			N
		>::type
	>
> : boost::true_type {};
}
}
}
}

#endif
