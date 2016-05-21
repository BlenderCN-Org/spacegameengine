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


#include <sge/input/processor.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/discover_event.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/discover_event.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system.hpp>
#include <sge/wlinput/initial_objects.hpp>
#include <sge/wlinput/processor.hpp>
#include <sge/wlinput/cursor/object.hpp>
#include <sge/wlinput/focus/object.hpp>
#include <awl/backends/posix/event_fwd.hpp>
#include <awl/backends/posix/posted.hpp>
#include <awl/backends/posix/processor.hpp>
#include <awl/backends/wayland/system/event/processor.hpp>
#include <awl/backends/wayland/system/event/seat.hpp>
#include <awl/backends/wayland/system/event/seat_callback.hpp>
#include <awl/backends/wayland/system/seat/caps.hpp>
#include <awl/backends/wayland/system/seat/object.hpp>
#include <awl/system/event/processor.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/optional_auto_connection.hpp>


sge::wlinput::processor::processor(
	sge::window::object const &,
	sge::window::system const &_system
)
:
	sge::input::processor(),
	system_processor_{
		fcppt::cast::dynamic_exn<
			awl::backends::wayland::system::event::processor &
		>(
			_system.awl_system_event_processor()
		)
	},
	focus_discover_{},
	focus_remove_{},
	cursor_discover_{},
	cursor_remove_{},
	cursors_(
		sge::wlinput::initial_objects<
			sge::wlinput::cursor::object,
			awl::backends::wayland::system::seat::caps::pointer
		>(
			system_processor_.seats()
		)
	),
	foci_(
		sge::wlinput::initial_objects<
			sge::wlinput::focus::object,
			awl::backends::wayland::system::seat::caps::keyboard
		>(
			system_processor_.seats()
		)
	),
	start_event_{
		system_processor_.fd_processor().post(
			awl::backends::posix::callback{
				std::bind(
					&sge::wlinput::processor::init,
					this,
					std::placeholders::_1
				)
			}
		)
	},
	seat_connection_{
		system_processor_.seat_callback(
			awl::backends::wayland::system::event::seat_callback{
				std::bind(
					&sge::wlinput::processor::seat_changed,
					this,
					std::placeholders::_1
				)
			}
		)
	}
{
}

sge::wlinput::processor::~processor()
{
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::keyboard_discover_callback(
	sge::input::keyboard::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::keyboard_remove_callback(
	sge::input::keyboard::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::mouse_discover_callback(
	sge::input::mouse::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::mouse_remove_callback(
	sge::input::mouse::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::focus_discover_callback(
	sge::input::focus::discover_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			focus_discover_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::focus_remove_callback(
	sge::input::focus::remove_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			focus_remove_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::cursor_discover_callback(
	sge::input::cursor::discover_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			cursor_discover_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::cursor_remove_callback(
	sge::input::cursor::remove_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			cursor_remove_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::joypad_discover_callback(
	sge::input::joypad::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::joypad_remove_callback(
	sge::input::joypad::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

void
sge::wlinput::processor::init(
	awl::backends::posix::event const &
)
{
	for(
		auto const &focus
		:
		foci_
	)
		focus_discover_(
			sge::input::focus::discover_event{
				*focus.second
			}
		);

	for(
		auto const &cursor
		:
		cursors_
	)
		cursor_discover_(
			sge::input::cursor::discover_event{
				*cursor.second
			}
		);
}

void
sge::wlinput::processor::seat_changed(
	awl::backends::wayland::system::event::seat const &_seat
)
{
	if(
		_seat.added().get()
	)
		this->add_seat(
			_seat.get()
		);
	else
		this->remove_seat(
			_seat.get()
		);
}

void
sge::wlinput::processor::add_seat(
	awl::backends::wayland::system::seat::object const &_seat
)
{
}

void
sge::wlinput::processor::remove_seat(
	awl::backends::wayland::system::seat::object const &_seat
)
{
}
