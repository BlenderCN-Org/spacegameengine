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


#ifndef SGE_EVDEV_DEVICE_MAKE_INFO_CONTAINER_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_MAKE_INFO_CONTAINER_HPP_INCLUDED

#include <sge/evdev/device/basic_info_decl.hpp>
#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/device/event_type_value.hpp>
#include <sge/evdev/device/read_bits_result.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

template<
	typename Id,
	typename Info,
	sge::evdev::device::event_type_value BitCount,
	typename Function
>
sge::evdev::device::basic_info<
	Id,
	Info
> const
make_info_container(
	typename sge::evdev::device::read_bits_result<
		BitCount
	>::type const &_bits,
	Function const &_function
)
{
	typedef sge::evdev::device::basic_info<
		Id,
		Info
	> basic_info;

	typedef typename basic_info::info_container info_container;

	typedef typename info_container::vector result_vector;

	result_vector ids;

	typedef typename basic_info::event_map_type result_map;

	result_map event_map;

	typedef typename sge::evdev::device::read_bits_result<
		BitCount
	>::type bit_container;

	for(
		sge::evdev::device::event_type index(
			0
		);
		index.get() < bit_container::static_size::value;
		++index
	)
	{
		if(
			_bits & index.get()
		)
		{
			event_map.insert(
				std::make_pair(
					index,
					fcppt::strong_typedef_construct_cast<
						typename basic_info::id
					>(
						ids.size()
					)
				)
			);

			ids.push_back(
				_function(
					index
				)
			);
		}
	}

	return
		basic_info(
			info_container(
				ids
			),
			event_map
		);
}

}
}
}

#endif
