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


#include <sge/input/keyboard/is_alt.hpp>
#include <sge/input/keyboard/is_ctrl.hpp>
#include <sge/input/keyboard/is_shift.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/optional_modifier.hpp>
#include <sge/input/keyboard/to_modifier.hpp>
#include <fcppt/optional_impl.hpp>


sge::input::keyboard::optional_modifier const
sge::input::keyboard::to_modifier(
	key_code::type const _code
)
{
	if(
		keyboard::is_ctrl(
			_code
		)
	)
		return
			sge::input::keyboard::optional_modifier(
				modifier::ctrl
			);

	if(
		keyboard::is_alt(
			_code
		)
	)
		return
			sge::input::keyboard::optional_modifier(
				modifier::alt
			);

	if(
		keyboard::is_shift(
			_code
		)
	)
		return
			sge::input::keyboard::optional_modifier(
				modifier::shift
			);

	return sge::input::keyboard::optional_modifier();
}
