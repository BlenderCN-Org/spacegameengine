/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_INPUT_CURSOR_BUTTON_EVENT_HPP_INCLUDED
#define SGE_INPUT_CURSOR_BUTTON_EVENT_HPP_INCLUDED

#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/detail/symbol.hpp>


namespace sge
{
namespace input
{
namespace cursor
{

class button_event
{
public:
	SGE_INPUT_DETAIL_SYMBOL
	button_event(
		sge::input::cursor::button_code,
		sge::input::cursor::position,
		sge::input::cursor::button_pressed
	);

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::button_code
	button_code() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::position const
	position() const;

	SGE_INPUT_DETAIL_SYMBOL
	bool
	pressed() const;
private:
	sge::input::cursor::button_code button_code_;

	sge::input::cursor::position position_;

	sge::input::cursor::button_pressed pressed_;
};

}
}
}

#endif
