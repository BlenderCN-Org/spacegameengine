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


#include <boost/foreach.hpp> // some header breaks BOOST_FOREACH
#include <X11/Xlib.h>
#include "../processor.hpp"
#include "../mouse.hpp"
#include "../keyboard.hpp"
#include "../device.hpp"
#include <sge/x11/display.hpp>
#include <sge/x11/window.hpp>
#include <sge/log/global.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <ostream>

sge::x11input::processor::processor(
	x11::window_ptr const _wnd
)
:
	wnd_(_wnd),
	acquired_(false),
	devices_(),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				wnd_->register_callback(
					FocusIn,
					std::tr1::bind(
						&processor::on_acquire,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				wnd_->register_callback(
					FocusOut,
					std::tr1::bind(
						&processor::on_release,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				wnd_->register_callback(
					MapNotify,
					std::tr1::bind(
						&processor::on_acquire,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				wnd_->register_callback(
					UnmapNotify,
					std::tr1::bind(
						&processor::on_release,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)
{
	/*
	connections.connect(
		wnd->register_callback(
			EnterNotify,
			std::tr1::bind(
				&processor::on_acquire,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	connections.connect(
		wnd->register_callback(
			LeaveNotify,
			std::tr1::bind(
				&processor::on_release,
				this,
				std::tr1::placeholders::_1
			)
		)
	);
*/
	fcppt::container::ptr::push_back_unique_ptr(
		devices_,
		fcppt::make_unique_ptr<
			x11input::mouse
		>(
			wnd_
		)
	);

	fcppt::container::ptr::push_back_unique_ptr(
		devices_,
		fcppt::make_unique_ptr<
			x11input::keyboard
		>(
			wnd_
		)
	);
}

sge::x11input::processor::~processor()
{
}

fcppt::signal::auto_connection
sge::x11input::processor::keyboard_discover_callback(
	input::keyboard::discover_callback const &_callback
)
{
	return fcppt::signal::auto_connection();
}

fcppt::signal::auto_connection
sge::x11input::processor::keyboard_remove_callback(
	input::keyboard::remove_callback const &_callback
)
{
	return fcppt::signal::auto_connection();
}

sge::input::keyboard::device_vector const
sge::x11input::processor::keyboards() const
{
}

fcppt::signal::auto_connection
sge::x11input::processor::mouse_discover_callback(
	input::mouse::discover_callback const &_callback
)
{
	return fcppt::signal::auto_connection();
}

fcppt::signal::auto_connection
sge::x11input::processor::mouse_remove_callback(
	input::mouse::remove_callback const &_callback
)
{
	return fcppt::signal::auto_connection();
}

sge::input::mouse::device_vector const
sge::x11input::processor::mice() const
{
}

void
sge::x11input::processor::dispatch()
{
}

sge::window::instance_ptr const
sge::x11input::processor::window() const
{
	return wnd_;
}

void
sge::x11input::processor::on_acquire(
	XEvent const &
)
{
	if(
		acquired_
	)
		return;

	acquired_ = true;

	FCPPT_LOG_DEBUG(
		log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("x11: acquire window")
	);

	BOOST_FOREACH(
		device_vector::reference dev,
		devices_
	)
		dev.grab();

	wnd_->display()->sync();
}

void
sge::x11input::processor::on_release(
	XEvent const &
)
{
	if(
		!acquired_
	)
		return;

	acquired_ = false;

	FCPPT_LOG_DEBUG(
		log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("x11: release window")
	);

	BOOST_FOREACH(
		device_vector::reference dev,
		devices_
	)
		dev.ungrab();
}
