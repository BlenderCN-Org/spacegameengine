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


#ifndef SGE_PARSE_JSON_START_HPP_INCLUDED
#define SGE_PARSE_JSON_START_HPP_INCLUDED

#include <sge/parse/symbol.hpp>
#include <sge/parse/json/array_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <sge/parse/json/start_fwd.hpp>
#include <sge/parse/json/start_variant.hpp>


namespace sge
{
namespace parse
{
namespace json
{

struct start
{
	SGE_PARSE_SYMBOL
	start();

	SGE_PARSE_SYMBOL
	explicit
	start(
		sge::parse::json::start_variant const &
	);

	SGE_PARSE_SYMBOL
	sge::parse::json::array &
	array();

	SGE_PARSE_SYMBOL
	sge::parse::json::array const &
	array() const;

	SGE_PARSE_SYMBOL
	sge::parse::json::object &
	object();

	SGE_PARSE_SYMBOL
	sge::parse::json::object const &
	object() const;

	sge::parse::json::start_variant variant;
};

}
}
}

#endif
