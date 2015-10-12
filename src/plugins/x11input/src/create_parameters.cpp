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


#include <sge/x11input/create_parameters.hpp>
#include <sge/x11input/device/id.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::create_parameters::create_parameters(
	sge::x11input::device::id const _id,
	XIDeviceInfo const &_info
)
:
	id_(
		_id
	),
	info_(
		_info
	)
{
}

sge::x11input::device::id
sge::x11input::create_parameters::id() const
{
	return
		id_;
}

XIDeviceInfo const &
sge::x11input::create_parameters::info() const
{
	return
		info_;
}
