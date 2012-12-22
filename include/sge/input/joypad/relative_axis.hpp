/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_INPUT_JOYPAD_RELATIVE_AXIS_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_RELATIVE_AXIS_HPP_INCLUDED

#include <sge/input/symbol.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/relative_axis_fwd.hpp>
#include <sge/input/joypad/relative_axis_id.hpp>


namespace sge
{
namespace input
{
namespace joypad
{

class relative_axis
{
public:
	SGE_INPUT_SYMBOL
	relative_axis(
		sge::input::joypad::axis_code,
		sge::input::joypad::relative_axis_id
	);

	SGE_INPUT_SYMBOL
	sge::input::joypad::axis_code
	code() const;

	SGE_INPUT_SYMBOL
	sge::input::joypad::relative_axis_id const
	id() const;
private:
	sge::input::joypad::axis_code code_;

	sge::input::joypad::relative_axis_id id_;
};

}
}
}

#endif
