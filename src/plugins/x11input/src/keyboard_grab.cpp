/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../keyboard_grab.hpp"
#include "../handle_grab.hpp"
#include <X11/Xlib.h>
#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>

sge::x11input::keyboard_grab::keyboard_grab(
	x11::window_ptr const wnd)
:
	wnd(wnd)
{
	handle_grab(
		XGrabKeyboard(
			wnd->display()->get(),
			wnd->get_window(),
			True,
			GrabModeAsync,
			GrabModeAsync,
			CurrentTime));
}

sge::x11input::keyboard_grab::~keyboard_grab()
{
	XUngrabKeyboard(
		wnd->display()->get(),
		CurrentTime);
}
