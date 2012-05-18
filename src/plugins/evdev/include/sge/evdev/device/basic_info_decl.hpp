/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_EVDEV_DEVICE_BASIC_INFO_DECL_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_BASIC_INFO_DECL_HPP_INCLUDED

#include <sge/evdev/device/basic_info_fwd.hpp>
#include <sge/evdev/device/event_map.hpp>
#include <sge/input/info/container.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

template<
	typename Id,
	typename Info
>
class basic_info
{
public:
	typedef sge::input::info::container<
		Id,
		Info
	> info_container;

	typedef Id id;

	typedef typename sge::evdev::device::event_map<
		id
	>::type event_map_type;

	basic_info(
		info_container const &,
		event_map_type const &
	);

	info_container const &
	infos();

	event_map_type const &
	event_map() const;
private:
	info_container infos_;

	event_map_type event_map_;
};

}
}
}

#endif
