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


#ifndef SGE_PARSE_JSON_MEMBER_NOT_FOUND_HPP_INCLUDED
#define SGE_PARSE_JSON_MEMBER_NOT_FOUND_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace parse
{
namespace json
{

class SGE_CORE_DETAIL_CLASS_SYMBOL member_not_found
:
	public sge::parse::json::exception
{
public:
	SGE_PARSE_JSON_DETAIL_SYMBOL
	explicit
	member_not_found(
		fcppt::string &&
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	member_not_found(
		member_not_found &&
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	member_not_found(
		member_not_found const &
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	member_not_found &
	operator=(
		member_not_found &&
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	member_not_found &
	operator=(
		member_not_found const &
	);

	SGE_PARSE_JSON_DETAIL_SYMBOL
	~member_not_found() noexcept
	override;
};

}
}
}

#endif
