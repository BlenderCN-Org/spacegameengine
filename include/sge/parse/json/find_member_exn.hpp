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


#ifndef SGE_PARSE_JSON_FIND_MEMBER_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_EXN_HPP_INCLUDED

#include <sge/parse/json/find_member_value_exn.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{

/// Searches for a member with the name @a name
/**
 * @throws member_not_found if the member is not found
 * @throws invalid_get if the member has a different type than T
*/
template<
	typename T,
	typename Arg
>
typename boost::mpl::if_<
	std::is_const<
		Arg
	>,
	T const &,
	T &
>::type
find_member_exn(
	Arg &_members,
	fcppt::string const &_name
)
{
	return
		sge::parse::json::get_exn<
			T
		>(
			sge::parse::json::find_member_value_exn(
				_members,
				_name
			)
		);
}

}
}
}

#endif
