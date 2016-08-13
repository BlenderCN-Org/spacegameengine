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


#include <sge/input/joypad/ff/end_magnitude.hpp>
#include <sge/input/joypad/ff/envelope.hpp>
#include <sge/input/joypad/ff/ramp.hpp>
#include <sge/input/joypad/ff/start_magnitude.hpp>


sge::input::joypad::ff::ramp::ramp(
	sge::input::joypad::ff::start_magnitude const _start_magnitude,
	sge::input::joypad::ff::end_magnitude const _end_magnitude,
	sge::input::joypad::ff::envelope const &_envelope
)
:
	start_magnitude_{
		_start_magnitude
	},
	end_magnitude_{
		_end_magnitude
	},
	envelope_{
		_envelope
	}
{
}

sge::input::joypad::ff::start_magnitude
sge::input::joypad::ff::ramp::start_magnitude() const
{
	return
		start_magnitude_;
}

sge::input::joypad::ff::end_magnitude
sge::input::joypad::ff::ramp::end_magnitude() const
{
	return
		end_magnitude_;
}

sge::input::joypad::ff::envelope const &
sge::input::joypad::ff::ramp::envelope() const
{
	return
		envelope_;
}
