/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2007       Simon Stienen    (s.stienen@slashlife.org)

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


#ifndef SGE_X11_WINDOW_HPP_INCLUDED
#define SGE_X11_WINDOW_HPP_INCLUDED

#include "display_fwd.hpp"
#include "visual_fwd.hpp"
#include "colormap_fwd.hpp"
#include "../window.hpp"
#include "../export.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <boost/function.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/signals.hpp>
#include <set>

namespace sge
{
namespace x11
{

class SGE_CLASS_SYMBOL window : public sge::window {
	friend class sge::window;
public:
	typedef int x11_event_type;
	typedef long x11_event_mask_type;

	typedef void x11_function_type(XEvent const &);
	typedef boost::function<x11_function_type> x11_callback_type;

	SGE_SYMBOL window(
		window_pos const &,
		window_size const &,
		string const &title,
		display_ptr,
		bool fullscreen,
		const_visual_ptr,
		colormap_ptr);
	SGE_SYMBOL ~window();

	SGE_SYMBOL void title(string const &title);
	SGE_SYMBOL void size(window_size const &sz);
	SGE_SYMBOL window_size const size() const;
	SGE_SYMBOL window_pos const viewport_offset() const;
	SGE_SYMBOL bool fullscreen() const;

	SGE_SYMBOL Window get_window() const;
	SGE_SYMBOL int screen() const;
	SGE_SYMBOL display_ptr const display() const;
	SGE_SYMBOL const_visual_ptr const visual() const;
	SGE_SYMBOL void map();
	SGE_SYMBOL void map_raised();

	SGE_SYMBOL boost::signals::connection register_callback(
		x11_event_type,
		x11_callback_type const &);
private:
	Display* dsp_() const;

	void add_event_mask(x11_event_type);

	display_ptr         dsp;
	const_visual_ptr    visual_;
	const_colormap_ptr  colormap_;
	int                 screen_;
	Window              wnd;
	bool                fullscreen_;
	x11_event_mask_type event_mask;

	typedef boost::signal<x11_function_type> x11_signal_type;
	typedef boost::ptr_map<x11_event_type, x11_signal_type> signal_map;
	signal_map signals;

	typedef std::set<window*> instance_map;
	static instance_map instances;
};

typedef shared_ptr<window> window_ptr;

}
}

#endif
