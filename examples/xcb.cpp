/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/xcb/connection.hpp>
#include <sge/xcb/flush.hpp>
#include <sge/xcb/screen.hpp>
#include <sge/xcb/screen_from_connection.hpp>
#include <sge/xcb/window/object.hpp>
#include <sge/xcb/window/create.hpp>
#include <sge/xcb/window/scoped_ptr.hpp>
#include <sge/xcb/window/pos.hpp>
#include <sge/xcb/window/dim.hpp>
#include <sge/xcb/window/depth.hpp>
#include <sge/xcb/window/border_width.hpp>
#include <sge/xcb/window/class.hpp>
#include <sge/xcb/window/attribute_list.hpp>
#include <fcppt/chrono/seconds.hpp>
#include <fcppt/time/sleep_any.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

int main()
{
	sge::xcb::connection connection_;

	sge::xcb::screen const screen_(
		sge::xcb::screen_from_connection(
			connection_
		)
	);

	sge::xcb::window::scoped_ptr wnd(
		sge::xcb::window::create(
			connection_,
			screen_.root_window(),
			sge::xcb::window::pos::null(),
			sge::xcb::window::dim(
				1024u,
				768u
			),
			sge::xcb::window::depth(
				static_cast<sge::xcb::window::depth::value_type>(
					32u
				)
			),
			sge::xcb::window::border_width(
				static_cast<sge::xcb::window::border_width::value_type>(
					0u
				)
			),
			sge::xcb::window::class_::input_output,
			screen_.root_visual(),
			sge::xcb::window::attribute_list()
		)
	);
	
	wnd->map();

	sge::xcb::flush(
		connection_
	);

	fcppt::time::sleep_any(
		fcppt::chrono::seconds(
			5
		)
	);
}
