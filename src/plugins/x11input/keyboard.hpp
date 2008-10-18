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


#ifndef SGE_X11INPUT_KEYBOARD_HPP_INCLUDED
#define SGE_X11INPUT_KEYBOARD_HPP_INCLUDED

#include "device.hpp"
#include <X11/Xlib.h>
#include <sge/input/callback.hpp>
#include <sge/signals/connection_manager.hpp>
#include <sge/x11/window_fwd.hpp>
#include <boost/scoped_ptr.hpp>

namespace sge
{
namespace x11input
{

class keyboard_grab;

class keyboard : public device {
public:
	keyboard(
		x11::window_ptr,
		input::callback const &,
		input::repeat_callback const &);
private:
	void grab();
	void ungrab();

	void on_key_event(
		XEvent const &);
	
	x11::window_ptr const        wnd;
	input::callback const        callback;
	input::repeat_callback const repeat_callback;
	bool const                   need_grab;

	signals::connection_manager connections;

	boost::scoped_ptr<
		keyboard_grab
	>                            grab_;
};

}
}

#endif
