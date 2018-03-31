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


#ifndef SGE_PARSE_JSON_FIND_MEMBER_VALUE_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_VALUE_EXN_HPP_INCLUDED

#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/member_not_found.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{

template<
	typename Arg
>
std::conditional_t<
	std::is_const<
		Arg
	>::value,
	sge::parse::json::value const &,
	sge::parse::json::value &
>
find_member_value_exn(
	Arg &_members,
	fcppt::string const &_name
)
{
	return
		fcppt::optional::to_exception(
			sge::parse::json::find_member_value(
				_members,
				_name
			),
			[
				&_name
			]{
				return
					sge::parse::json::member_not_found(
						FCPPT_TEXT("Cannot find member \"")
						+
						_name
						+
						FCPPT_TEXT("\" in a json object's member list!")
					);
			}
		).get();
}

}
}
}

#endif
