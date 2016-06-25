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


#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/wlinput/cursor/position.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-util.h>
#include <fcppt/config/external_end.hpp>


sge::input::cursor::position
sge::wlinput::cursor::position(
	wl_fixed_t const _x,
	wl_fixed_t const _y
)
{
	auto const convert(
		[](
			wl_fixed_t const _val
		)
		->
		sge::input::cursor::position_unit
		{
			return
				::wl_fixed_to_int(
					_val
				);
		}
	);

	return
		sge::input::cursor::position{
			convert(
				_x
			),
			convert(
				_y
			)
		};
}
