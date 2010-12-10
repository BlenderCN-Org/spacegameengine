/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <X11/Xlib.h>
#include "../get_pointer.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/text.hpp>

sge::x11input::mouse_pos const
sge::x11input::get_pointer(
	awl::backends::x11::window::instance_ptr const _window
)
{
	Window
		root_return,
		child_return;
	int
		root_x_return,
		root_y_return,
		win_x_return,
		win_y_return;

	unsigned mask_return;

	if(
		::XQueryPointer(
			_window->display()->get(),
			_window->get(),
			&root_return,
			&child_return,
			&root_x_return,
			&root_y_return,
			&win_x_return,
			&win_y_return,
			&mask_return
		)
		== False
	)
		throw sge::input::exception(
			FCPPT_TEXT("XQueryPointer failed!")
		);

	return
		x11input::mouse_pos(
			win_x_return,
			win_y_return
		);
}
