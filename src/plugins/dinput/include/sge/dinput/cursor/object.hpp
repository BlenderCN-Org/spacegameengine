/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_DINPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_DINPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/cursor/object_fwd.hpp>
#include <sge/dinput/cursor/temp_acquire_fwd.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_signal.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_signal.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <awl/backends/windows/event/type.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_fwd.hpp>
#include <awl/backends/windows/window/event/return_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace dinput
{
namespace cursor
{

class object
:
	public sge::input::cursor::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		awl::backends::windows::window::event::processor &,
		awl::backends::windows::window::object &,
		IDirectInputDevice8 *system_mouse
	);

	~object();

	fcppt::signal::auto_connection
	button_callback(
		sge::input::cursor::button_callback const &
	);

	fcppt::signal::auto_connection
	move_callback(
		sge::input::cursor::move_callback const &
	);

	sge::input::cursor::optional_position const
	position() const;

	void
	mode(
		sge::input::cursor::mode::type
	);

	void
	acquire();

	bool
	unacquire();
private:
	awl::backends::windows::window::event::return_type
	on_move(
		awl::backends::windows::window::event::object const &
	);

	awl::backends::windows::window::event::return_type
	on_button(
		awl::backends::windows::window::event::object const &,
		sge::input::cursor::button_code::type,
		bool down
	);

	awl::backends::windows::window::event::return_type
	on_temp_unacquire(
		awl::backends::windows::event::type,
		awl::backends::windows::window::event::object const &
	);

	awl::backends::windows::window::event::return_type
	on_temp_acquire(
		awl::backends::windows::event::type,
		awl::backends::windows::window::event::object const &
	);

	void
	update_grab();

	awl::backends::windows::window::event::processor &event_processor_;

	awl::backends::windows::window::object &window_;

	IDirectInputDevice8 *const system_mouse_;

	sge::input::cursor::button_signal button_signal_;

	sge::input::cursor::move_signal move_signal_;

	typedef fcppt::scoped_ptr<
		sge::dinput::cursor::temp_acquire
	> temp_acquire_scoped_ptr;

	temp_acquire_scoped_ptr temp_acquire_;

	fcppt::signal::connection_manager const connections_;
};

}
}
}

#endif
