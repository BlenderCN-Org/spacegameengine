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


#ifndef SGE_CON_CONSOLE_GFX_HPP_INCLUDED
#define SGE_CON_CONSOLE_GFX_HPP_INCLUDED

#include "../font/font.hpp"
#include "../renderer/device.hpp"
#include "../input/system.hpp"
#include "../scoped_connection.hpp"
#include "../sprite/system.hpp"
#include "../sprite/object.hpp"
#include "../time/timer.hpp"
#include "../texture/part.hpp"
#include "../string.hpp"
#include "../export.hpp"
#include "action_var.hpp"
#include "arg_list.hpp"
#include <boost/noncopyable.hpp>
#include <deque>
#include <cstddef>

namespace sge
{
namespace con
{

class console_gfx : boost::noncopyable {
public:
	SGE_SYMBOL console_gfx(
		renderer::device_ptr,
		texture::part_ptr,
		font::font_ptr,
		input::system_ptr,
		sprite::point const &,
		sprite::dim const &);
	SGE_SYMBOL void key_callback(const input::key_pair &);
	SGE_SYMBOL void key_action(const input::key_type &);
	SGE_SYMBOL void draw();
	SGE_SYMBOL space_unit change_cursor_rate(
		const space_unit &n,
		const space_unit &);
	SGE_SYMBOL void toggle(); 
	SGE_SYMBOL bool active() const;
	SGE_SYMBOL void print(const string &);
	SGE_SYMBOL void clear(const arg_list &);
	SGE_SYMBOL void dump(const arg_list &);

private:
	void tabcomplete(string &);

	typedef std::deque<string> history_container;

	const renderer::device_ptr rend;
	const font::font_ptr fn;
	scoped_connection ic,irc;
	sprite::system ss;
	sprite::object bg;
	bool active_;

	// input and history stuff
	time::timer cursor_timer;
	action_var<space_unit>::type cursor_rate;
	bool cursor_active;
	string::value_type cursor_char;
	string il;
	string::size_type cursor_pos;
	history_container history;
	history_container input_history;
	history_container::iterator history_pos;
	history_container::iterator input_history_pos;
	std::size_t history_size;
};

}
}

#endif
