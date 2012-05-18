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


#ifndef SGE_EVDEV_JOYPAD_EVENT_MAP_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_EVENT_MAP_HPP_INCLUDED

#include <sge/evdev/device/event_map.hpp>
#include <sge/input/joypad/absolute_axis_id.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/relative_axis_id.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{

class event_map
{
public:
	typedef sge::evdev::device::event_map<
		sge::input::joypad::absolute_axis_id
	>::type absolute_axis_map;

	typedef sge::evdev::device::event_map<
		sge::input::joypad::button_id
	>::type button_map;

	typedef sge::evdev::device::event_map<
		sge::input::joypad::relative_axis_id
	>::type relative_axis_map;

	event_map(
		absolute_axis_map const &,
		button_map const &,
		relative_axis_map const &
	);

	absolute_axis_map const &
	absolute_axis() const;

	button_map const &
	buttons() const;

	relative_axis_map const &
	relative_axis() const;
private:
	absolute_axis_map absolute_axis_;

	button_map buttons_;

	relative_axis_map relative_axis_;
};

}
}
}

#endif
