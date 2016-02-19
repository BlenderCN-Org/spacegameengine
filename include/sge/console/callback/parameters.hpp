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


#ifndef SGE_CONSOLE_CALLBACK_PARAMETERS_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_PARAMETERS_HPP_INCLUDED

#include <sge/console/long_description.hpp>
#include <sge/console/short_description.hpp>
#include <sge/console/callback/function.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/detail/symbol.hpp>
#include <sge/font/string.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace console
{
namespace callback
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	SGE_CONSOLE_DETAIL_SYMBOL
	parameters(
		sge::console::callback::function const &,
		sge::console::callback::name const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::callback::parameters &
	short_description(
		sge::font::string const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::callback::parameters &
	long_description(
		sge::font::string const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::callback::function const &
	function() const;

	SGE_CONSOLE_DETAIL_SYMBOL
	sge::font::string const &
	name() const;

	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::short_description const &
	short_description() const;

	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::long_description const &
	long_description() const;
private:
	sge::console::callback::function const function_;

	sge::font::string const name_;

	sge::console::short_description short_description_;

	sge::console::long_description long_description_;
};

}
}
}

#endif
