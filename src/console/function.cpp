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


#include <sge/console/function.hpp>
#include <sge/console/signal.hpp>
#include <sge/font/text/string.hpp>


sge::console::function::function(
	font::text::string const &_short_description,
	font::text::string const &_long_description
)
:
	signal_(),
	short_description_(
		_short_description),
	long_description_(
		_long_description)
{}

sge::console::function::~function()
{
}

sge::console::signal &
sge::console::function::signal()
{
	return signal_;
}

sge::font::text::string const &
sge::console::function::short_description() const
{
	return short_description_;
}

sge::font::text::string const &
sge::console::function::long_description() const
{
	return long_description_;
}
