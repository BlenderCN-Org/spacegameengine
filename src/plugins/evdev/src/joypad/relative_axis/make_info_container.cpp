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


#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/device/make_info_container.hpp>
#include <sge/evdev/device/read_bits.hpp>
#include <sge/evdev/joypad/relative_axis/info_container.hpp>
#include <sge/evdev/joypad/relative_axis/make_info.hpp>
#include <sge/evdev/joypad/relative_axis/make_info_container.hpp>
#include <sge/input/joypad/relative_axis_id.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::relative_axis::info_container
sge::evdev::joypad::relative_axis::make_info_container(
	sge::evdev::device::fd const &_fd
)
{
	return
		sge::evdev::device::make_info_container<
			sge::input::joypad::relative_axis_id,
			sge::input::joypad::relative_axis_info,
			REL_CNT
		>(
			sge::evdev::device::read_bits<
				REL_CNT
			>(
				_fd,
				EV_REL
			),
			&sge::evdev::joypad::relative_axis::make_info
		);
}
