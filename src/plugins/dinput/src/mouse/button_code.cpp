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


#include <sge/dinput/mouse/button_code.hpp>
#include <sge/dinput/cast_key.hpp>
#include <sge/dinput/di.hpp>

sge::input::mouse::button_code::type
sge::dinput::mouse::button_code(
	DWORD const _code
)
{
	if(
		_code == dinput::cast_key(DIMOFS_BUTTON0)
	)
		return sge::input::mouse::button_code::left;
	else if(
		_code == dinput::cast_key(DIMOFS_BUTTON1)
	)
		return sge::input::mouse::button_code::right;
	else if(
		_code == dinput::cast_key(DIMOFS_BUTTON2)
	)
		return sge::input::mouse::button_code::middle;

	return sge::input::mouse::button_code::unknown;
}