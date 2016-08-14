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


#include <sge/x11input/send_init_event.hpp>
#include <awl/backends/x11/atom.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/backends/x11/window/event/mask.hpp>
#include <awl/backends/x11/window/event/object.hpp>
#include <awl/backends/x11/window/event/send.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


void
sge::x11input::send_init_event(
	awl::backends::x11::window::object const &_window,
	awl::backends::x11::atom const _atom
)
{
	XClientMessageEvent client_message{
		ClientMessage,
		0ul, // serial
		True, // send_event
		_window.display().get(),
		_window.get(),
		_atom.get(),
		8, // format
		{{0}}
	};

	XEvent event;

	event.type = ClientMessage;
	event.xclient = client_message;

	awl::backends::x11::window::event::send(
		_window,
		awl::backends::x11::window::event::mask(
			NoEventMask
		),
		awl::backends::x11::window::event::object(
			event
		)
	);
}
