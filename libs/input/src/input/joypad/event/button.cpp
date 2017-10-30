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


#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/button_pressed.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/base.hpp>
#include <sge/input/joypad/event/button.hpp>


sge::input::joypad::event::button::button(
	sge::input::joypad::shared_ptr const _joypad,
	sge::input::joypad::button_id const _button_id,
	sge::input::joypad::button_pressed const _pressed
)
:
	sge::input::joypad::event::base{
		_joypad
	},
	button_id_{
		_button_id
	},
	pressed_{
		_pressed
	}
{
}

sge::input::joypad::event::button::~button()
{
}

sge::input::joypad::button_id
sge::input::joypad::event::button::button_id() const
{
	return
		button_id_;
}

bool
sge::input::joypad::event::button::pressed() const
{
	return
		pressed_.get();
}
