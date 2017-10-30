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


#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_id.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/x11input/mouse/button.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::input::mouse::button
sge::x11input::mouse::button(
	XIDeviceEvent const  &_event,
	sge::input::mouse::button_info_container const &_info
)
{
	int const detail(
		_event.detail
	);

	FCPPT_ASSERT_PRE(
		detail > 0
	);

	sge::input::mouse::button_id const id(
		static_cast<
			sge::input::mouse::button_id::value_type
		>(
			detail - 1 // TODO: why?
		)
	);

	FCPPT_ASSERT_PRE(
		id < _info.size()
	);

	return
		sge::input::mouse::button(
			_info[
				id
			].code(),
			id
		);
}
