/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_INPUT_JOYPAD_ABSOLUTE_AXIS_INFO_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_ABSOLUTE_AXIS_INFO_HPP_INCLUDED

#include <sge/input/joypad/absolute_axis_info_fwd.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/axis_max.hpp>
#include <sge/input/joypad/axis_min.hpp>
#include <sge/input/info/optional_string.hpp>
#include <sge/input/symbol.hpp>

namespace sge
{
namespace input
{
namespace joypad
{

class absolute_axis_info
{
public:
	SGE_INPUT_SYMBOL
	absolute_axis_info(
		joypad::axis_code::type,
		input::info::optional_string const &,
		joypad::axis_min,
		joypad::axis_max
	);

	SGE_INPUT_SYMBOL
	joypad::axis_code::type
	code() const;

	SGE_INPUT_SYMBOL
	input::info::optional_string const &
	name() const;

	SGE_INPUT_SYMBOL
	joypad::axis_min const
	min() const;

	SGE_INPUT_SYMBOL
	joypad::axis_max const
	max() const;
private:
	joypad::axis_code::type code_;

	input::info::optional_string name_;

	joypad::axis_min min_;

	joypad::axis_max max_;
};

}
}
}

#endif
