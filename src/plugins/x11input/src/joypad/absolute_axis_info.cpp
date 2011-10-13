/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/x11input/joypad/absolute_axis_info.hpp>
#include <sge/x11input/joypad/axis_code.hpp>
#include <sge/x11input/joypad/axis_value.hpp>
#include <sge/x11input/device/info/string_from_atom.hpp>
#include <sge/input/info/optional_string.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/axis_max.hpp>
#include <sge/input/joypad/axis_min.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::input::joypad::absolute_axis_info const
sge::x11input::joypad::absolute_axis_info(
	XIValuatorClassInfo const &_info,
	awl::backends::x11::display &_display
)
{
	sge::input::info::optional_string const name(
		x11input::device::info::string_from_atom(
			_display,
			_info.label
		)
	);

	return
		sge::input::joypad::absolute_axis_info(
			joypad::axis_code(
				name
			),
			name,
			sge::input::joypad::axis_min(
				x11input::joypad::axis_value(
					_info.min
				)
			),
			sge::input::joypad::axis_max(
				x11input::joypad::axis_value(
					_info.max
				)
			)
		);
}
