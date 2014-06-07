/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PARSE_JSON_CONVERT_TO_STATIC_CONTAINER_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_TO_STATIC_CONTAINER_HPP_INCLUDED

#include <sge/parse/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/choose_fundamental.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/text.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace convert
{

template<
	typename Container
>
Container
to_static_container(
	sge::parse::json::array const &_array
)
{
	if(
		_array.elements.size()
		!=
		static_cast<
			sge::parse::json::element_vector::size_type
		>(
			Container::dim_wrapper::value
		)
	)
		throw sge::parse::exception(
			FCPPT_TEXT("convert::to_static_container: unequal amount of elements!")
		);

	Container result{
		fcppt::no_init()
	};

	for(
		sge::parse::json::element_vector::size_type index(
			0u
		);
		index < _array.elements.size();
		++index
	)
		result[
			static_cast<
				typename
				Container::size_type
			>(
				index
			)
		] =
			static_cast<
				typename Container::value_type
			>(
				sge::parse::json::get<
					typename
					sge::parse::json::convert::choose_fundamental<
						typename
						Container::value_type
					>::type
				>(
					_array.elements[
						index
					]
				)
			);

	return result;
}

}
}
}
}

#endif
