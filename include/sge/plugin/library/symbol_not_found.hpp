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


#ifndef SGE_PLUGIN_LIBRARY_SYMBOL_NOT_FOUND_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_SYMBOL_NOT_FOUND_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/plugin/symbol.hpp>
#include <sge/plugin/library/exception.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace plugin
{
namespace library
{

class SGE_CLASS_SYMBOL symbol_not_found
:
	public sge::plugin::library::exception
{
public:
	SGE_PLUGIN_SYMBOL
	symbol_not_found(
		fcppt::string const &,
		library::symbol_string const &
	);

	SGE_PLUGIN_SYMBOL
	fcppt::string const &
	library_name() const;

	SGE_PLUGIN_SYMBOL
	library::symbol_string const &
	symbol() const;

	SGE_PLUGIN_SYMBOL
	~symbol_not_found() throw()
	override;
private:
	fcppt::string library_name_;

	sge::plugin::library::symbol_string symbol_;
};

}
}
}

#endif
