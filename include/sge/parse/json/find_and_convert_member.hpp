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


#ifndef SGE_PARSE_JSON_FIND_AND_CONVERT_MEMBER_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_AND_CONVERT_MEMBER_HPP_INCLUDED

#include <sge/parse/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/convert_from.hpp>
#include <sge/parse/json/find_object_exn.hpp>
#include <sge/parse/json/invalid_get.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <iterator>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{
template<typename T>
typename
boost::mpl::if_
<
	boost::mpl::or_
	<
		std::is_same
		<
			typename std::remove_const<T>::type,
			sge::parse::json::value
		>,
		boost::mpl::or_
		<
			std::is_same
			<
				typename std::remove_const<T>::type,
				sge::parse::json::object
			>,
			boost::mpl::or_
			<
				std::is_same
				<
					typename std::remove_const<T>::type,
					sge::parse::json::array
				>
			>
		>
	>,
	T const &,
	T const
>::type
find_and_convert_member(
	sge::parse::json::object const &o,
	sge::parse::json::path const &input_path)
{
	FCPPT_ASSERT_PRE(
		!input_path.empty());

	sge::parse::json::path const shortened_path =
		sge::parse::json::path(
			input_path.begin(),
			std::prev(
				input_path.end()));

	sge::parse::json::object const &found_object =
		sge::parse::json::find_object_exn(
			o,
			shortened_path);

	sge::parse::json::member_map::const_iterator it(
		found_object.members.find(
			input_path.back()));

	if (it == found_object.members.end())
		throw
			sge::parse::exception(
				FCPPT_TEXT("Couldn't find member \"")+
				input_path.back()+
				FCPPT_TEXT("\" in the object \"")+
				sge::parse::json::path_to_string(
					shortened_path)+
				FCPPT_TEXT("\""));

	try
	{
		return
			sge::parse::json::convert_from<T>(
				it->second);
	}
	catch (sge::parse::json::invalid_get const &e)
	{
		throw
			sge::parse::exception(
				FCPPT_TEXT("Unable to parse member \"")+
				it->first+
				FCPPT_TEXT("\" of object \"")+
				sge::parse::json::path_to_string(
					shortened_path)+
				FCPPT_TEXT("\": ")+
				e.string());
	}
}
}
}
}

#endif
