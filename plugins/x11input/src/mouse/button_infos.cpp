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


#include <sge/input/mouse/button_info.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/x11input/device/info/string_from_atom.hpp>
#include <sge/x11input/mouse/button_code.hpp>
#include <sge/x11input/mouse/button_infos.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::input::mouse::button_info_container::vector
sge::x11input::mouse::button_infos(
	XIButtonClassInfo const &_info,
	awl::backends::x11::display &_display
)
{
	return
		fcppt::algorithm::map<
			sge::input::mouse::button_info_container::vector
		>(
			fcppt::make_int_range_count(
				_info.num_buttons
			),
			[
				&_info,
				&_display
			](
				int const _button_index
			)
			{
				fcppt::optional_string const name(
					sge::x11input::device::info::string_from_atom(
						_display,
						_info.labels[
							_button_index
						]
					)
				);

				return
					sge::input::mouse::button_info(
						sge::x11input::mouse::button_code(
							name
						),
						name
					);
			}
		);
}
