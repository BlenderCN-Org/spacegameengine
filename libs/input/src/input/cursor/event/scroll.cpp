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


#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/scroll_code.hpp>
#include <sge/input/cursor/scroll_value.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <sge/input/cursor/event/scroll.hpp>


sge::input::cursor::event::scroll::scroll(
	sge::input::cursor::shared_ptr const _cursor,
	sge::input::cursor::scroll_code const _code,
	sge::input::cursor::scroll_value const _value
)
:
	sge::input::cursor::event::scroll::base{
		_cursor
	},
	code_{
		_code
	},
	value_{
		_value
	}
{
}

sge::input::cursor::event::scroll::~scroll()
{
}

sge::input::cursor::scroll_code
sge::input::cursor::event::scroll::code() const
{
	return
		code_;
}

sge::input::cursor::scroll_value
sge::input::cursor::event::scroll::value() const
{
	return
		value_;
}
