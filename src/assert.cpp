/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/assert.hpp>
#include <sge/exception.hpp>
#include <sge/sstream.hpp>
#include <ostream>

void sge::detail::process_assert(
	string const &file,
	string const &line,
	string const &condition,
	string const &message,
	string const &function)
{
	ostringstream ss;
	
	ss << file << SGE_TEXT(':') << line;
	
	if (!function.empty())
		ss << SGE_TEXT(" function '") << function << SGE_TEXT('\'');
	ss << SGE_TEXT(": assertion failed: ") << condition;
	
	if (!message.empty())
		ss << SGE_TEXT(", ") << message;

	throw exception(ss.str());
}
