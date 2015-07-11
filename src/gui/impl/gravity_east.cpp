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


#include <sge/gui/gravity.hpp>
#include <sge/gui/impl/gravity_east.hpp>
#include <fcppt/assert/unreachable.hpp>


bool
sge::gui::impl::gravity_east(
	sge::gui::gravity const _gravity
)
{
	switch(
		_gravity
	)
	{
		case sge::gui::gravity::north_west:
		case sge::gui::gravity::south_west:
			return
				false;
		case sge::gui::gravity::south_east:
		case sge::gui::gravity::north_east:
			return
				true;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
