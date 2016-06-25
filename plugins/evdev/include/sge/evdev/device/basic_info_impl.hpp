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


#ifndef SGE_EVDEV_DEVICE_BASIC_INFO_IMPL_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_BASIC_INFO_IMPL_HPP_INCLUDED

#include <sge/evdev/device/basic_info_decl.hpp>


template<
	typename Id,
	typename Info
>
sge::evdev::device::basic_info<
	Id,
	Info
>::basic_info(
	info_container const &_infos,
	event_map_type const &_event_map
)
:
	infos_(
		_infos
	),
	event_map_(
		_event_map
	)
{
}

template<
	typename Id,
	typename Info
>
typename
sge::evdev::device::basic_info<
	Id,
	Info
>::info_container const &
sge::evdev::device::basic_info<
	Id,
	Info
>::infos() const
{
	return
		infos_;
}

template<
	typename Id,
	typename Info
>
typename
sge::evdev::device::basic_info<
	Id,
	Info
>::event_map_type const &
sge::evdev::device::basic_info<
	Id,
	Info
>::event_map() const
{
	return
		event_map_;
}

#endif
