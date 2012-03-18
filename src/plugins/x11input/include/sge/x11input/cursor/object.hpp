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


#ifndef SGE_X11INPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_signal.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_signal.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/x11input/cursor/grab_fwd.hpp>
#include <sge/x11input/cursor/image.hpp>
#include <sge/x11input/cursor/object_fwd.hpp>
#include <sge/x11input/device/object.hpp>
#include <sge/x11input/device/parameters_fwd.hpp>
#include <sge/x11input/device/window_event_fwd.hpp>
#include <awl/backends/x11/window/instance_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/math/vector/object_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace x11input
{
namespace cursor
{

class object
:
	public sge::input::cursor::object,
	public sge::x11input::device::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		x11input::device::parameters const &,
		cursor::image invisible_pixmap,
		bool entered
	);

	~object();

	void
	on_focus_in();

	void
	on_focus_out();

	void
	on_leave();
private:
	fcppt::signal::auto_connection
	button_callback(
		input::cursor::button_callback const &
	);

	fcppt::signal::auto_connection
	move_callback(
		input::cursor::move_callback const &
	);

	input::cursor::optional_position const
	position() const;

	void
	mode(
		input::cursor::mode::type
	);

	void
	on_motion(
		x11input::device::window_event const &
	);

	void
	on_button_down(
		x11input::device::window_event const &
	);

	void
	on_button_up(
		x11input::device::window_event const &
	);

	void
	button_event(
		x11input::device::window_event const &,
		bool pressed
	);

	void
	move_event();

	void
	check_grab();

	awl::backends::x11::window::instance const &window_;

	cursor::image const invisible_image_;

	fcppt::signal::connection_manager const connections_;

	sge::input::cursor::mode::type mode_;

	bool entered_;

	sge::input::cursor::optional_position position_;

	sge::input::cursor::button_signal button_signal_;

	sge::input::cursor::move_signal move_signal_;

	fcppt::scoped_ptr<
		x11input::cursor::grab
	> cursor_grab_;
};

}
}
}

#endif
