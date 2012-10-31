/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PARSE_INI_OUTPUT_TO_RANGE_HPP_INCLUDED
#define SGE_PARSE_INI_OUTPUT_TO_RANGE_HPP_INCLUDED

#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/output/grammar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/karma_generate.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace ini
{
namespace output
{

template<
	typename Out
>
bool
to_range(
	Out &_beg,
	sge::parse::ini::start const &_data
)
{
	sge::parse::ini::output::grammar<
		Out
	> parser;

	return
		boost::spirit::karma::generate(
			_beg,
			parser,
			_data
		);
}

}
}
}
}

#endif
