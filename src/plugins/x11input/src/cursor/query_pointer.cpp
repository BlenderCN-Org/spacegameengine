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


#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/x11input/cursor/query_pointer.hpp>
#include <sge/x11input/device/id.hpp>
#include <awl/backends/x11/deleter.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::input::cursor::optional_position const
sge::x11input::cursor::query_pointer(
	awl::backends::x11::window::instance const &_window,
	device::id const &_id
)
{
	Window
		root_return,
		child_return;

	double
		root_x_return,
		root_y_return,
		win_x_return,
		win_y_return;

	XIButtonState buttons_return;

	XIModifierState modifiers_return;

	XIGroupState group_return;

	if(
		::XIQueryPointer(
			_window.display().get(),
			_id.get(),
			_window.get(),
			&root_return,
			&child_return,
			&root_x_return,
			&root_y_return,
			&win_x_return,
			&win_y_return,
			&buttons_return,
			&modifiers_return,
			&group_return
		)
		== False
	)
		return sge::input::cursor::optional_position();

	typedef fcppt::scoped_ptr<
		unsigned char,
		awl::backends::x11::deleter
	> scoped_mask;

	scoped_mask scoped_buttons_mask(
		buttons_return.mask
	);

	return
		sge::input::cursor::optional_position(
			input::cursor::position(
				static_cast<
					input::cursor::position_unit
				>(
					win_x_return
				),
				static_cast<
					input::cursor::position_unit
				>(
					win_y_return
				)
			)
		);
}
