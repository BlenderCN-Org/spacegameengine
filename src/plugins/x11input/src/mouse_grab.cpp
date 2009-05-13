/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include "../mouse_grab.hpp"
#include "../handle_grab.hpp"
#include <X11/Xlib.h>
#include <sge/time/sleep.hpp>
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>
#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>
#include <sge/x11/cursor.hpp>
#include <sge/x11/sentry.hpp>
#include <sge/exception.hpp>

sge::x11input::mouse_grab::mouse_grab(
	x11::window_ptr const wnd,
	x11::cursor const &cur)
:
	wnd(wnd)
{
	SGE_X11_SENTRY

	for(;;)
	{
		try
		{
			handle_grab(
				XGrabPointer(
					wnd->display()->get(),
					wnd->get(),
					True,
					PointerMotionMask
					| ButtonPressMask
					| ButtonReleaseMask,
					GrabModeAsync,
					GrabModeAsync,
					wnd->get(),
					cur.get(),
					CurrentTime));
			return;
		}
		catch(exception const &)
		{
			time::sleep(
				time::second(
					1
				)
			);
		}
	}
}

sge::x11input::mouse_grab::~mouse_grab()
{
	SGE_X11_SENTRY

	XUngrabPointer(
		wnd->display()->get(),
		CurrentTime
	);
}
