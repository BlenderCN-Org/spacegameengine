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


#ifndef SGE_OPENGL_PARSE_EXTENSIONS_HPP_INCLUDED
#define SGE_OPENGL_PARSE_EXTENSIONS_HPP_INCLUDED

#include <sge/opengl/extension_set.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{

template<
	typename Type
>
sge::opengl::extension_set<
	Type
>
parse_extensions(
	std::string const &_extensions
)
{
	std::istringstream stream(
		_extensions
	);

	typedef
	std::istream_iterator<
		std::string
	>
	iterator;

	return
		fcppt::algorithm::map<
			sge::opengl::extension_set<
				Type
			>
		>(
			boost::make_iterator_range(
				iterator(
					stream
				),
				iterator()
			),
			[](
				std::string const &_element
			)
			{
				return
					Type(
						std::move(
							_element
						)
					);
			}
		);
}

}
}

#endif
