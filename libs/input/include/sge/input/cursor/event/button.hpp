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


#ifndef SGE_INPUT_CURSOR_EVENT_BUTTON_HPP_INCLUDED
#define SGE_INPUT_CURSOR_EVENT_BUTTON_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <sge/input/cursor/event/button_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace input
{
namespace cursor
{
namespace event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL button
:
	public sge::input::cursor::event::base
{
	FCPPT_NONCOPYABLE(
		button
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	button(
		sge::input::cursor::shared_ptr,
		sge::input::cursor::button_code,
		sge::input::cursor::position,
		sge::input::cursor::button_pressed
	);

	SGE_INPUT_DETAIL_SYMBOL
	~button()
	override;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::button_code
	button_code() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::position
	position() const;

	SGE_INPUT_DETAIL_SYMBOL
	bool
	pressed() const;
private:
	sge::input::cursor::button_code const button_code_;

	sge::input::cursor::position const position_;

	sge::input::cursor::button_pressed const pressed_;
};

}
}
}
}

#endif
