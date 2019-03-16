/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PARSE_JSON_CONVERT_CHOOSE_FUNDAMENTAL_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_CHOOSE_FUNDAMENTAL_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace convert
{

template<
	typename Type,
	typename Enable = void
>
struct choose_fundamental;

template<
	typename Type
>
struct choose_fundamental<
	Type,
	std::enable_if_t<
		std::is_integral_v<
			Type
		>
	>
>
{
	typedef
	sge::parse::json::int_type
	type;
};

template<
	typename Type
>
struct choose_fundamental<
	Type,
	std::enable_if_t<
		std::is_floating_point_v<
			Type
		>
	>
>
{
	typedef
	sge::parse::json::float_type
	type;
};

template<
	typename Type
>
struct choose_fundamental<
	Type,
	std::enable_if_t<
		std::is_same_v<
			Type,
			sge::charconv::utf8_string
		>
	>
>
{
	typedef
	sge::charconv::utf8_string
	type;
};

}
}
}
}

#endif
