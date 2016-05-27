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


#include <sge/wlinput/xkb_context_fwd.hpp>
#include <sge/wlinput/focus/create.hpp>
#include <sge/wlinput/focus/create_function.hpp>
#include <sge/wlinput/focus/object.hpp>
#include <awl/backends/wayland/seat_fwd.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::wlinput::focus::create_function
sge::wlinput::focus::create(
	sge::wlinput::xkb_context const &_context,
	awl::backends::wayland::window::object const &_window
)
{
	return
		sge::wlinput::focus::create_function{
			[
				&_context,
				&_window
			](
				awl::backends::wayland::seat const &_seat
			)
			{
				return
					fcppt::make_unique_ptr<
						sge::wlinput::focus::object
					>(
						_context,
						_window,
						_seat
					);
			}
		};
}
