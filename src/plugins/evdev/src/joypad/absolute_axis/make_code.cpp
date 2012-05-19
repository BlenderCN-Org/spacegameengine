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


#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/joypad/absolute_axis/make_code.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


sge::input::joypad::axis_code::type
sge::evdev::joypad::absolute_axis::make_code(
	sge::evdev::device::event_type const _event
)
{
	switch(
		_event.get()
	)
	{
	case ABS_X:
		return sge::input::joypad::axis_code::x;
	case ABS_Y:
		return sge::input::joypad::axis_code::y;
	case ABS_Z:
		return sge::input::joypad::axis_code::z;
	case ABS_RX:
	case ABS_RY:
	case ABS_RZ:
	case ABS_THROTTLE:
	case ABS_RUDDER:
	case ABS_WHEEL:
	case ABS_GAS:
	case ABS_BRAKE:
	case ABS_HAT0X:
	case ABS_HAT0Y:
	case ABS_HAT1X:
	case ABS_HAT1Y:
	case ABS_HAT2X:
	case ABS_HAT2Y:
	case ABS_HAT3X:
	case ABS_HAT3Y:
	case ABS_PRESSURE:
	case ABS_DISTANCE:
	case ABS_TILT_X:
	case ABS_TILT_Y:
	case ABS_TOOL_WIDTH:
	case ABS_VOLUME:
	case ABS_MISC:
	// TODO: discard multi touch stuff?
	case ABS_MT_SLOT:
	case ABS_MT_TOUCH_MAJOR:
	case ABS_MT_TOUCH_MINOR:
	case ABS_MT_WIDTH_MAJOR:
	case ABS_MT_WIDTH_MINOR:
	case ABS_MT_ORIENTATION:
	case ABS_MT_POSITION_X:
	case ABS_MT_POSITION_Y:
	case ABS_MT_TOOL_TYPE:
	case ABS_MT_BLOB_ID:
	case ABS_MT_TRACKING_ID:
	case ABS_MT_PRESSURE:
	case ABS_MT_DISTANCE:
	default:
		return sge::input::joypad::axis_code::unknown;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
