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


#include <sge/input/event_base.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::input::mouse::event::base::base(
	sge::input::mouse::shared_ptr _mouse
)
:
	sge::input::event_base{
		_mouse->window()
	},
	mouse_{
		std::move(
			_mouse
		)
	}
{
}

sge::input::mouse::event::base::~base()
{
}

sge::input::mouse::shared_ptr const &
sge::input::mouse::event::base::mouse() const
{
	return
		mouse_;
}
