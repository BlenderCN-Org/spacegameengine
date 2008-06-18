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


#include <X11/Xlib.h>
#include <X11/X.h>
#ifdef USE_DGA
#include <X11/extensions/xf86dga.h>
#endif
#include "../system.hpp"
#include "../pointer.hpp"
#include "../translation.hpp"
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/input/key_type.hpp>
#include <sge/util.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <cstring>
#include <ostream>

sge::xinput::system::system(const x_window_ptr wnd)
 : wnd(wnd),
   colormap(XDefaultColormap(wnd->display()->get(), wnd->screen())),
   black_(wnd->display(), colormap),
   no_bmp_(wnd->display(), wnd->get_window()),
   no_cursor_(wnd->display(), no_bmp_.pixmap(), black_.color()),
#ifdef USE_DGA
   dga_guard_(wnd->display(), wnd->screen()),
   use_dga(true)
#else
   use_dga(false)
#endif
{
#ifdef USE_DGA
	int flags;
	if(XF86DGAQueryDirectVideo(wnd->display()->get(),wnd->screen(),&flags)==false)
		throw exception(SGE_TEXT("XF86DGAQueryDirectVideo() failed!"));
	if(flags & XF86DGADirectMouse)
	{
		sge::cerr << SGE_TEXT("You compiled spacegameengine with use_dga=1 but DGA Mouse is not supported by your system! Maybe you are missing libXxf86dga or a proper video driver? Disabling dga.\n");
		use_dga = false;
	}
#endif
	if(!use_dga)
		mouse_last = get_mouse_pos(wnd->display(), wnd);

	add_connection(wnd->register_callback(KeyPress, boost::bind(&system::on_key_event, this, _1)));
	add_connection(wnd->register_callback(KeyRelease, boost::bind(&system::on_key_event, this, _1)));
	add_connection(wnd->register_callback(ButtonPress, boost::bind(&system::on_button_event, this, _1)));
	add_connection(wnd->register_callback(ButtonRelease, boost::bind(&system::on_button_event, this, _1)));
	add_connection(wnd->register_callback(MotionNotify, boost::bind(&system::on_motion_event, this, _1)));
	add_connection(wnd->register_callback(EnterNotify, boost::bind(&system::on_acquire, this, _1)));
	add_connection(wnd->register_callback(LeaveNotify, boost::bind(&system::on_release, this, _1)));
	add_connection(wnd->register_callback(FocusIn, boost::bind(&system::on_acquire, this, _1)));
	add_connection(wnd->register_callback(FocusOut, boost::bind(&system::on_release, this, _1)));
	add_connection(wnd->register_callback(MapNotify, boost::bind(&system::on_acquire, this, _1)));
	add_connection(wnd->register_callback(UnmapNotify, boost::bind(&system::on_release, this, _1)));

}

sge::xinput::system::~system()
{
	if(wnd->fullscreen())
		XUngrabKeyboard(wnd->display()->get(), CurrentTime);
	XUngrabPointer(wnd->display()->get(), CurrentTime);
}

sge::callback_connection sge::xinput::system::register_callback(
	const callback& c)
{
	return sig.connect(c);
}

sge::callback_connection sge::xinput::system::register_repeat_callback(
	const repeat_callback& c)
{
	return repeat_sig.connect(c);
}

void sge::xinput::system::dispatch()
{
}

sge::window_ptr sge::xinput::system::get_window() const
{
	return wnd;
}

void sge::xinput::system::add_connection(const boost::signals::connection con)
{
	connections.push_back(new boost::signals::scoped_connection(con));
}

void sge::xinput::system::grab()
{
	grab_pointer();
	if(wnd->fullscreen())
		grab_keyboard();
	XSync(wnd->display()->get(), False);
}

void sge::xinput::system::grab_pointer()
{
	for(;;)
		if(handle_grab(
			XGrabPointer(
				wnd->display()->get(),
				wnd->get_window(),
				True,
				PointerMotionMask
					| ButtonPressMask
					| ButtonReleaseMask,
				GrabModeAsync,
				GrabModeAsync,
				wnd->get_window(),
				no_cursor_.cursor(),
				CurrentTime)))
			return;
}

void sge::xinput::system::grab_keyboard()
{
	for(;;)
		if(handle_grab(
			XGrabKeyboard(
				wnd->display()->get(),
				wnd->get_window(),
				True,
				GrabModeAsync,
				GrabModeAsync,
				CurrentTime)))
			return;
}

bool sge::xinput::system::handle_grab(const int r) const
{
	switch(r) {
	case GrabSuccess:
		return true;
	case GrabFrozen:
		throw exception(SGE_TEXT("x11: Grab frozen!"));
	case GrabNotViewable:
	case AlreadyGrabbed:
		break;
	case GrabInvalidTime:
		throw exception(SGE_TEXT("x11: GrabInvalidTime!"));
	}

	sleep(100);
	return false;
}

void sge::xinput::system::on_motion_event(const XEvent& xev)
{
	if(use_dga)
		dga_motion(xev);
	else
		warped_motion(xev);
}

void sge::xinput::system::on_key_event(const XEvent& xev)
{
	// check for repeated key (thanks to SDL)
	if(xev.type == KeyRelease && XPending(wnd->display()->get()))
	{
		XEvent peek;
		XPeekEvent(wnd->display()->get(), &peek);
		if(peek.type == KeyPress &&
		   peek.xkey.keycode == xev.xkey.keycode &&
		   (peek.xkey.time - xev.xkey.time) < 2)
		{
			XNextEvent(wnd->display()->get(), &peek);
			repeat_sig(create_key_type(xev));
			return;
		}
	}

	sig(input::key_pair(create_key_type(xev), xev.type == KeyRelease ? 0 : 1));
}

sge::input::key_type sge::xinput::system::create_key_type(const XEvent& xev)
{
	XComposeStatus state;
	KeySym ks;
	boost::array<char,32> keybuf;

	const int num_chars = XLookupString(
		const_cast<XKeyEvent*>(reinterpret_cast<const XKeyEvent*>(&xev)),
		keybuf.c_array(),
		static_cast<int>(keybuf.size()),
		&ks,
		&state);
	const char code = keybuf[0];

	if(num_chars > 1)
	{
		sge::cerr << SGE_TEXT("stub: character '") << code << SGE_TEXT("' in XLookupString has ") << num_chars << SGE_TEXT(" bytes!\n");
		return input::key_type();
	}

	return input::key_type(get_key_name(ks), get_key_code(ks), code);
}

void sge::xinput::system::on_button_event(const XEvent& xev)
{
	sig(input::key_pair(mouse_key(xev.xbutton.button), xev.type == ButtonRelease ? 0 : 1));
}

void sge::xinput::system::on_release(const XEvent&)
{
	enable_dga(false);
	XUngrabPointer(wnd->display()->get(), CurrentTime);
}

void sge::xinput::system::on_acquire(const XEvent&)
{
	grab();
	enable_dga(true);
}

void sge::xinput::system::enable_dga(const bool
#ifdef USE_DGA
		enable
#endif
)
{
#ifdef USE_DGA
	if(!use_dga)
		return;
	_dga_guard.enable(enable);
#endif
}

sge::input::key_type sge::xinput::system::mouse_key(const unsigned x11code) const
{
	switch(x11code) {
	case 1:
		return mouse_l;
	case 2:
		return mouse_m;
	case 3:
		return mouse_r;
	default:
		return undefined_mouse_key;
	}
}

sge::input::key_type::string sge::xinput::system::get_key_name(const KeySym ks) const
{
	const char* const name = XKeysymToString(ks);
	return name ? input::key_type::string(name,name+std::strlen(name)) : SGE_TEXT("unknown");
}

sge::input::key_code sge::xinput::system::get_key_code(const KeySym ks) const
{
	return translate_key_code(ks);
}

void sge::xinput::system::private_mouse_motion(const mouse_coordinate_t deltax, const mouse_coordinate_t deltay)
{
	if(deltax)
		sig(input::key_pair(mouse_x, deltax));
	if(deltay)
		sig(input::key_pair(mouse_y, deltay));
}

void sge::xinput::system::dga_motion(XEvent xevent)
{
	mouse_coordinate_t dx = xevent.xmotion.x_root,
	                   dy = xevent.xmotion.y_root;

	while(XCheckTypedEvent(wnd->display()->get(), MotionNotify, &xevent))
	{
		dx += xevent.xmotion.x_root;
		dy += xevent.xmotion.y_root;
	}

	private_mouse_motion(dx, dy);
}

// thanks to SDL
void sge::xinput::system::warped_motion(XEvent xevent)
{
	const mouse_coordinate_t MOUSE_FUDGE_FACTOR = 8;

	const mouse_coordinate_t w = wnd->width(),
	                         h = wnd->height();
	mouse_coordinate_t deltax = xevent.xmotion.x - mouse_last.x(),
	                   deltay = xevent.xmotion.y - mouse_last.y();

	mouse_last.x() = xevent.xmotion.x;
	mouse_last.y() = xevent.xmotion.y;

	private_mouse_motion(deltax, deltay);

	if ( !((xevent.xmotion.x < MOUSE_FUDGE_FACTOR) ||
	     (xevent.xmotion.x > (w-MOUSE_FUDGE_FACTOR)) ||
	     (xevent.xmotion.y < MOUSE_FUDGE_FACTOR) ||
	     (xevent.xmotion.y > (h-MOUSE_FUDGE_FACTOR)) ))
		return;

	while ( XCheckTypedEvent(wnd->display()->get(), MotionNotify, &xevent) )
	{
		deltax = xevent.xmotion.x - mouse_last.x();
		deltay = xevent.xmotion.y - mouse_last.y();

		mouse_last.x() = xevent.xmotion.x;
		mouse_last.y() = xevent.xmotion.y;

		private_mouse_motion(deltax, deltay);
	}
	mouse_last.x() = w/2;
	mouse_last.y() = h/2;
	XWarpPointer(wnd->display()->get(), None, wnd->get_window(), 0, 0, 0, 0, mouse_last.x(), mouse_last.y());

	const unsigned max_loops = 10;
	for(unsigned i = 0; i < max_loops; ++i )
	{
		XMaskEvent(wnd->display()->get(), PointerMotionMask, &xevent);
		if ( (xevent.xmotion.x > mouse_last.x() - MOUSE_FUDGE_FACTOR) &&
		     (xevent.xmotion.x < mouse_last.x() + MOUSE_FUDGE_FACTOR) &&
		     (xevent.xmotion.y > mouse_last.y() - MOUSE_FUDGE_FACTOR) &&
		     (xevent.xmotion.y < mouse_last.y() + MOUSE_FUDGE_FACTOR) )
			break;

		if(i == max_loops - 1)
			sge::cerr << SGE_TEXT("warning: didn't detect mouse warp motion! Try to enable dga mouse instead.\n");
	}
}

const sge::input::key_type sge::xinput::system::mouse_x(SGE_TEXT("mouse_x"), input::kc::mouse_x_axis);
const sge::input::key_type sge::xinput::system::mouse_y(SGE_TEXT("mouse_y"), input::kc::mouse_y_axis);
const sge::input::key_type sge::xinput::system::undefined_mouse_key(SGE_TEXT("undefined mouse key"));
const sge::input::key_type sge::xinput::system::mouse_l(SGE_TEXT("mouse_L"), input::kc::mouse_l);
const sge::input::key_type sge::xinput::system::mouse_r(SGE_TEXT("mouse_R"), input::kc::mouse_r);
const sge::input::key_type sge::xinput::system::mouse_m(SGE_TEXT("mouse_M"), input::kc::mouse_m);

