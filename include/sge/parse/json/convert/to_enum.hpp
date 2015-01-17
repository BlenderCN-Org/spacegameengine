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


#ifndef SGE_PARSE_JSON_CONVERT_TO_ENUM_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_TO_ENUM_HPP_INCLUDED

#include <sge/parse/exception.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
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
	typename Enum
>
typename boost::enable_if<
	std::is_enum<
		Enum
	>,
	Enum
>::type
to_enum(
	sge::parse::json::value const &_value,
	Enum const _max_value
)
{
	sge::parse::json::int_type const int_value(
		sge::parse::json::get<
			sge::parse::json::int_type
		>(
			_value
		)
	);

	if(
		int_value < 0
		||
		int_value
		>
		static_cast<
			sge::parse::json::int_type
		>(
			_max_value
		)
	)
		throw sge::parse::exception(
			FCPPT_TEXT("Enum value out of range!")
		);

	return
		static_cast<
			Enum
		>(
			int_value
		);
}

}
}
}
}

#endif
