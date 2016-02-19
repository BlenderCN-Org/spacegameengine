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


#include <sge/x11input/device/window_event.hpp>
#include <sge/x11input/focus/fake_core_event.hpp>
#include <sge/x11input/focus/to_base_event.hpp>
#include <sge/x11input/focus/translate_event.hpp>
#include <awl/backends/x11/window/event/filter.hpp>
#include <awl/backends/x11/window/event/object.hpp>


void
sge::x11input::focus::fake_core_event(
	awl::backends::x11::window::object const &_window,
	sge::x11input::device::window_event const &_event
)
{
	awl::backends::x11::window::event::filter(
		awl::backends::x11::window::event::object(
			sge::x11input::focus::to_base_event(
				sge::x11input::focus::translate_event(
					_event.get()
				)
			)
		),
		_window
	);
}
