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


#include "../event.hpp"
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

template<
	typename ValueType
>
sge::x11input::device::event<ValueType>::event(
	value_type const &_event
)
:
	event_(_event)
{
}

template<
	typename ValueType
>
typename sge::x11input::device::event<ValueType>::value_type const &
sge::x11input::device::event<ValueType>::get() const
{
	return event_;
}

template class
sge::x11input::device::event<
	XIDeviceEvent
>;

template class
sge::x11input::device::event<
	XIRawEvent
>;

template class
sge::x11input::device::event<
	XIHierarchyEvent
>;
