/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_code.hpp>
#include <sge/input/mouse/button_event.hpp>


sge::input::mouse::button_event::button_event(
	sge::input::mouse::button const &_button,
	bool const _pressed
)
:
	button_(
		_button
	),
	pressed_(
		_pressed
	)
{
}

sge::input::mouse::button_code
sge::input::mouse::button_event::button_code() const
{
	return button_.code();
}

sge::input::mouse::button const &
sge::input::mouse::button_event::button() const
{
	return button_;
}

bool
sge::input::mouse::button_event::pressed() const
{
	return pressed_;
}
