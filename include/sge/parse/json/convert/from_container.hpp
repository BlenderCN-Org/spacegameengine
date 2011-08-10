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


#ifndef SGE_PARSE_JSON_CONVERT_FROM_CONTAINER_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_FROM_CONTAINER_HPP_INCLUDED

#include <sge/parse/json/convert/choose_fundamental.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/algorithm/map.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/object/static_cast.hpp>

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
sge::parse::json::array const
from_container(
	Container const &_container
)
{
	return
		sge::parse::json::array(
			fcppt::algorithm::map<
				sge::parse::json::element_vector
			>(
				_container,
				boost::phoenix::static_cast_<
					typename convert::choose_fundamental<
						typename Container::value_type
					>::type
				>(
					boost::phoenix::arg_names::arg1
				)
			)
		);
}

}
}
}
}

#endif
