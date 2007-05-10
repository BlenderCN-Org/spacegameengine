/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_XINPUT_INPUT_SYSTEM_HPP
#define SGE_XINPUT_INPUT_SYSTEM_HPP

#include <cstddef>
#include <string>
#include <map>
#include <boost/signals/trackable.hpp>
#include "../../input/input_system.hpp"
#include "../../x_window.hpp"
#include "../../math/vector.hpp"
#include "x_color.hpp"
#include "x_pixmap.hpp"
#include "x_cursor.hpp"
#include "dga.hpp"

namespace sge
{
namespace xinput
{

class input_system : public sge::input_system, boost::signals::trackable {
public:
	input_system(x_window_ptr wnd);
	~input_system();
	boost::signals::connection register_callback(const callback& c);
	void dispatch();
private:
	typedef int mouse_coordinate_t;
	void grab();
	void grab_pointer();
	void grab_keyboard();
	bool handle_grab(int return_value) const;
	void enable_dga(bool);
	key_type mouse_key(unsigned x11code) const;
	void dga_motion(XEvent);
	void warped_motion(XEvent);
	void private_mouse_motion(mouse_coordinate_t deltax, mouse_coordinate_t deltay);

	void on_motion_event(const XEvent&);
	void on_key_event(const XEvent&);
	void on_button_event(const XEvent&);
	void on_acquire(const XEvent&);
	void on_release(const XEvent&);

	signal_type sig;

	key_code get_key_code(KeySym ks) const;
	std::string get_key_name(KeySym ks) const;

	x_window_ptr wnd;
	Colormap colormap;
	unsigned mmwidth;

	math::vector<mouse_coordinate_t,2> mouse_last;

	typedef std::map<unsigned,key_code> x11_to_sge_array;
	x11_to_sge_array x11tosge;

	x_color _black;
	x_pixmap _no_bmp;
	x_cursor _no_cursor;

#ifdef USE_DGA
	dga_guard _dga_guard;
#endif
	bool use_dga;
};

}
}

#endif

