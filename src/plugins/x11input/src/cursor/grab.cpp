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


#include <sge/input/exception.hpp>
#include <sge/x11input/logger.hpp>
#include <sge/x11input/cursor/grab.hpp>
#include <sge/x11input/device/id.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/cursor/object.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/time/sleep_any.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/X.h>
#include <X11/extensions/XInput2.h>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sge::x11input::cursor::grab::grab(
	awl::backends::x11::window::object const &_window,
	sge::x11input::device::id const _id,
	awl::backends::x11::cursor::object const &_cursor
)
:
	window_(
		_window
	),
	id_(
		_id
	)
{
	XIEventMask mask =
	{
		id_.get(),
		0,
		nullptr
	};

	for(
		;;
	)
	{
		Status const ret(
			::XIGrabDevice(
				_window.display().get(),
				_id.get(),
				_window.get(),
				CurrentTime,
				_cursor.get(),
				GrabModeAsync,
				GrabModeAsync,
				True,
				&mask
			)
		);

		switch(
			ret
		)
		{
		case GrabSuccess:
			return;
		case AlreadyGrabbed:
		case GrabNotViewable:
		case GrabFrozen:
			FCPPT_LOG_DEBUG(
				sge::x11input::logger(),
				fcppt::log::_
					<< FCPPT_TEXT("XIGrabDevice failed with code ")
					<< ret
					<< FCPPT_TEXT(". Retrying...")
			);

			fcppt::time::sleep_any(
				std::chrono::milliseconds(
					10
				)
			);
			break;
		case GrabInvalidTime:
		default:
			throw sge::input::exception(
				FCPPT_TEXT("X11 grab failed with code ")
				+ fcppt::insert_to_fcppt_string(
					ret
				)
			);
		}
	}
}

sge::x11input::cursor::grab::~grab()
{
	::XIUngrabDevice(
		window_.display().get(),
		id_.get(),
		CurrentTime
	);
}
