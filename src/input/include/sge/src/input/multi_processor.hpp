/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_INPUT_MULTI_PROCESSOR_HPP_INCLUDED
#define SGE_SRC_INPUT_MULTI_PROCESSOR_HPP_INCLUDED

#include <sge/input/processor.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/discover_event_fwd.hpp>
#include <sge/input/cursor/discover_signal.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/cursor/remove_event_fwd.hpp>
#include <sge/input/cursor/remove_signal.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/discover_event_fwd.hpp>
#include <sge/input/focus/discover_signal.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/focus/remove_event_fwd.hpp>
#include <sge/input/focus/remove_signal.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/discover_event_fwd.hpp>
#include <sge/input/joypad/discover_signal.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/joypad/remove_event_fwd.hpp>
#include <sge/input/joypad/remove_signal.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event_fwd.hpp>
#include <sge/input/keyboard/discover_signal.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event_fwd.hpp>
#include <sge/input/keyboard/remove_signal.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_event_fwd.hpp>
#include <sge/input/mouse/discover_signal.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_event_fwd.hpp>
#include <sge/input/mouse/remove_signal.hpp>
#include <sge/src/input/system_ptr_vector.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace input
{

class multi_processor
:
	public sge::input::processor
{
	FCPPT_NONCOPYABLE(
		multi_processor
	);
public:
	multi_processor(
		sge::window::object const &,
		sge::window::system const &,
		sge::input::system_ptr_vector const &
	);

	~multi_processor()
	override;
private:
	fcppt::signal::auto_connection
	keyboard_discover_callback(
		sge::input::keyboard::discover_callback const &
	)
	override;

	fcppt::signal::auto_connection
	keyboard_remove_callback(
		sge::input::keyboard::remove_callback const &
	)
	override;

	fcppt::signal::auto_connection
	mouse_discover_callback(
		sge::input::mouse::discover_callback const &
	)
	override;

	fcppt::signal::auto_connection
	mouse_remove_callback(
		sge::input::mouse::remove_callback const &
	)
	override;

	fcppt::signal::auto_connection
	focus_discover_callback(
		sge::input::focus::discover_callback const &
	)
	override;

	fcppt::signal::auto_connection
	focus_remove_callback(
		sge::input::focus::remove_callback const &
	)
	override;

	fcppt::signal::auto_connection
	cursor_discover_callback(
		sge::input::cursor::discover_callback const &
	)
	override;

	fcppt::signal::auto_connection
	cursor_remove_callback(
		sge::input::cursor::remove_callback const &
	)
	override;

	fcppt::signal::auto_connection
	joypad_discover_callback(
		sge::input::joypad::discover_callback const &
	)
	override;

	fcppt::signal::auto_connection
	joypad_remove_callback(
		sge::input::joypad::remove_callback const &
	)
	override;

	void
	on_keyboard_discover(
		sge::input::keyboard::discover_event const &
	);

	void
	on_keyboard_remove(
		sge::input::keyboard::remove_event const &
	);

	void
	on_mouse_discover(
		sge::input::mouse::discover_event const &
	);

	void
	on_mouse_remove(
		sge::input::mouse::remove_event const &
	);

	void
	on_focus_discover(
		sge::input::focus::discover_event const &
	);

	void
	on_focus_remove(
		sge::input::focus::remove_event const &
	);

	void
	on_cursor_discover(
		sge::input::cursor::discover_event const &
	);

	void
	on_cursor_remove(
		sge::input::cursor::remove_event const &
	);

	void
	on_joypad_discover(
		sge::input::joypad::discover_event const &
	);

	void
	on_joypad_remove(
		sge::input::joypad::remove_event const &
	);

	typedef
	std::vector<
		sge::input::processor_unique_ptr
	>
	processor_vector;

	processor_vector const processors_;

	sge::input::keyboard::discover_signal keyboard_discover_;

	sge::input::keyboard::remove_signal keyboard_remove_;

	sge::input::mouse::discover_signal mouse_discover_;

	sge::input::mouse::remove_signal mouse_remove_;

	sge::input::focus::discover_signal focus_discover_;

	sge::input::focus::remove_signal focus_remove_;

	sge::input::cursor::discover_signal cursor_discover_;

	sge::input::cursor::remove_signal cursor_remove_;

	sge::input::joypad::discover_signal joypad_discover_;

	sge::input::joypad::remove_signal joypad_remove_;

	typedef
	std::vector<
		fcppt::signal::auto_connection
	>
	connection_vector;

	connection_vector const connections_;
};

}
}

#endif
