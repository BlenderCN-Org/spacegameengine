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


#include "../mouse_axis_code.hpp"
#include "../cast_key.hpp"
#include "../di.hpp"

sge::input::mouse::axis::type
sge::dinput::mouse_axis_code(
	DWORD const _code
)
{
	if(
		_code == dinput::cast_key(DIMOFS_X)
	)
		return sge::input::mouse::axis::x;
	else if(
		_code == dinput::cast_key(DIMOFS_Y)
	)
		return sge::input::mouse::axis::y;
	else if(
		_code == dinput::cast_key(DIMOFS_Z)
	)
		return sge::input::mouse::axis::wheel;

	return sge::input::mouse::axis::unknown;
}