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


#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <sge/input/cursor/event/button.hpp>


sge::input::cursor::event::button::button(
	sge::input::cursor::shared_ptr const _cursor,
	sge::input::cursor::button_code const _button_code,
	sge::input::cursor::position const _position,
	sge::input::cursor::button_pressed const _pressed
)
:
	sge::input::cursor::event::base{
		_cursor
	},
	button_code_{
		_button_code
	},
	position_{
		_position
	},
	pressed_{
		_pressed
	}
{
}

sge::input::cursor::event::button::~button()
{
}

sge::input::cursor::button_code
sge::input::cursor::event::button::button_code() const
{
	return
		button_code_;
}

sge::input::cursor::position
sge::input::cursor::event::button::position() const
{
	return
		position_;
}

bool
sge::input::cursor::event::button::pressed() const
{
	return
		pressed_.get();
}
