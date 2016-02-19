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


#include <sge/x11input/mask_is_set.hpp>
#include <sge/x11input/device/valuator/callback.hpp>
#include <sge/x11input/device/valuator/foreach.hpp>
#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/value.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <climits>
#include <fcppt/config/external_end.hpp>


void
sge::x11input::device::valuator::foreach(
	XIValuatorState const &_valuators,
	sge::x11input::device::valuator::callback const &_callback
)
{
	double const *valuator{
		_valuators.values
	};

	for(
		int const index
		:
		fcppt::make_int_range_count(
			_valuators.mask_len
			*
			CHAR_BIT
		)
	)
		if(
			sge::x11input::mask_is_set(
				_valuators.mask,
				index
			)
		)
		{
			_callback(
				sge::x11input::device::valuator::index{
					index
				},
				sge::x11input::device::valuator::value(
					*valuator
				)
			);

			++valuator;
		}
}
