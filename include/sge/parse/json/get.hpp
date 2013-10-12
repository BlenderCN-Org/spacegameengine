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


#ifndef SGE_PARSE_JSON_GET_HPP_INCLUDED
#define SGE_PARSE_JSON_GET_HPP_INCLUDED

#include <sge/parse/json/invalid_get.hpp>
#include <sge/parse/json/detail/get_return_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/type_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{

template<
	typename T,
	typename Arg
>
typename
sge::parse::json::detail::get_return_type<
	T,
	Arg
>::type
get(
	Arg &_val
)
{
	typedef typename std::remove_const<
		T
	>::type real_type;

	if(
		!fcppt::variant::holds_type<
			real_type
		>(
			_val
		)
	)
		throw json::invalid_get(
			FCPPT_TEXT("json::get<")
			+ fcppt::type_name_from_info(
				typeid(T)
			)
			+ FCPPT_TEXT("> failed! Type is \"")
			+ fcppt::type_name_from_info(
				fcppt::variant::type_info(
					_val
				)
			)
			+ FCPPT_TEXT("\" instead!")
		);

	return
		_val. template get<
			real_type
		>();
}

}
}
}

#endif
