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


#ifndef SGE_PARSE_INI_ENTRY_HPP_INCLUDED
#define SGE_PARSE_INI_ENTRY_HPP_INCLUDED

#include <sge/parse/ini/entry_fwd.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/parse/ini/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace ini
{

struct entry
{
	SGE_PARSE_INI_DETAIL_SYMBOL
	entry(
		sge::parse::ini::entry_name &&,
		sge::parse::ini::value &&
	);

	std::string
		name,
		value;
};

SGE_PARSE_INI_DETAIL_SYMBOL
bool
operator==(
	sge::parse::ini::entry const &,
	sge::parse::ini::entry const &
);

}
}
}

#endif
