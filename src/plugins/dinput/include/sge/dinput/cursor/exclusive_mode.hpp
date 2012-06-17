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


#ifndef SGE_DINPUT_CURSOR_EXCLUSIVE_MODE_HPP_INCLUDED
#define SGE_DINPUT_CURSOR_EXCLUSIVE_MODE_HPP_INCLUDED

#include <sge/dinput/cursor/exclusive_mode_fwd.hpp>
#include <awl/backends/windows/event/type.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_fwd.hpp>
#include <awl/backends/windows/window/event/return_type_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/signal/connection_manager.hpp>


namespace sge
{
namespace dinput
{
namespace cursor
{

class exclusive_mode
{
	FCPPT_NONCOPYABLE(
		exclusive_mode
	);
public:
	exclusive_mode(
		awl::backends::windows::window::event::processor &,
		awl::backends::windows::window::object &
	);

	~exclusive_mode();
private:
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

	fcppt::signal::connection_manager::container const
	make_connections(
		awl::backends::windows::window::event::processor &
	);

	void
	make_connection_pair(
		fcppt::signal::connection_manager::container &,
		awl::backends::windows::window::event::processor &,
		awl::backends::windows::event::type::value_type enter_event,
		awl::backends::windows::event::type::value_type exit_event
	);

	typedef fcppt::optional<
		awl::backends::windows::event::type
	> optional_event_type;

	optional_event_type grab_event_;

	awl::backends::windows::window::object &window_;

	fcppt::signal::connection_manager const connections_;
};

}
}
}

#endif
