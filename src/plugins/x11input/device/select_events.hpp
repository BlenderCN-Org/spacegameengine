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


#ifndef SGE_X11INPUT_DEVICE_SELECT_EVENTS_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_SELECT_EVENTS_HPP_INCLUDED

#include "id.hpp"
#include <awl/backends/x11/system/event/type.hpp>
#include <awl/backends/x11/window/instance_fwd.hpp>

namespace sge
{
namespace x11input
{
namespace device
{

void
select_events(
	awl::backends::x11::window::instance &,
	x11input::device::id,
	awl::backends::x11::system::event::type,
	bool add
);

}
}
}

#endif
