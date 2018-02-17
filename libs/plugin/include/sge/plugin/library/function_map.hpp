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


#ifndef SGE_PLUGIN_LIBRARY_FUNCTION_MAP_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_FUNCTION_MAP_HPP_INCLUDED

#include <sge/plugin/detail/symbol.hpp>
#include <sge/plugin/library/function_base.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace plugin
{
namespace library
{

class function_map
{
public:
	typedef
	std::unordered_map<
		sge::plugin::library::symbol_string,
		sge::plugin::library::function_base
	>
	container;

	SGE_PLUGIN_DETAIL_SYMBOL
	explicit
	function_map(
		container &&
	);

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::library::function_base
	function(
		sge::plugin::library::symbol_string const &
	) const;

	SGE_PLUGIN_DETAIL_SYMBOL
	container const &
	get() const;
private:
	container functions_;
};

}
}
}

#endif
