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


#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/joypad/relative_axis/make_code.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


sge::input::joypad::axis_code
sge::evdev::joypad::relative_axis::make_code(
	sge::evdev::device::event_type const _event
)
{
	switch(
		_event.get()
	)
	{
	case REL_X:
		return sge::input::joypad::axis_code::x;
	case REL_Y:
		return sge::input::joypad::axis_code::y;
	case REL_Z:
		return sge::input::joypad::axis_code::z;
	case REL_RX:
	case REL_RY:
	case REL_RZ:
	case REL_HWHEEL:
	case REL_DIAL:
	case REL_WHEEL:
	case REL_MISC:
	default:
		return sge::input::joypad::axis_code::unknown;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
