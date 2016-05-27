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


#include <sge/input/cursor/scroll_code.hpp>
#include <sge/wlinput/cursor/scroll_code.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-client-protocol.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


sge::input::cursor::scroll_code
sge::wlinput::cursor::scroll_code(
	std::uint32_t const _code
)
{
	switch(
		_code
	)
	{
	case WL_POINTER_AXIS_VERTICAL_SCROLL:
		return
			sge::input::cursor::scroll_code::vertical;
	case WL_POINTER_AXIS_HORIZONTAL_SCROLL:
		return
			sge::input::cursor::scroll_code::horizontal;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
