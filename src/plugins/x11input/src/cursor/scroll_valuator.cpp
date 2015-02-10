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


#include <sge/input/cursor/scroll_code.hpp>
#include <sge/input/cursor/scroll_value.hpp>
#include <sge/x11input/cursor/scroll_valuator.hpp>
#include <sge/x11input/device/valuator/any.hpp>
#include <sge/x11input/device/valuator/update.hpp>
#include <sge/x11input/device/valuator/value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::x11input::cursor::scroll_valuator::scroll_valuator(
	sge::x11input::device::valuator::any const &_any,
	sge::input::cursor::scroll_code const _code
)
:
	any_(
		_any
	),
	code_(
		_code
	)
{
}

sge::input::cursor::scroll_code
sge::x11input::cursor::scroll_valuator::code() const
{
	return
		code_;
}

sge::input::cursor::scroll_value
sge::x11input::cursor::scroll_valuator::update(
	sge::x11input::device::valuator::value const _value
)
{
	std::pair<
		sge::input::cursor::scroll_value,
		sge::x11input::device::valuator::any
	> const result(
		sge::x11input::device::valuator::update<
			sge::input::cursor::scroll_value
		>(
			any_,
			_value
		)
	);

	any_ =
		result.second;

	return
		result.first;
}
