/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_X11INPUT_DEVICE_EVENT_DEMUXER_IMPL_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_EVENT_DEMUXER_IMPL_HPP_INCLUDED

#include <sge/x11input/device/demuxer_enabled.hpp>
#include <sge/x11input/device/event_data.hpp>
#include <sge/x11input/device/event_demuxer_decl.hpp>
#include <sge/x11input/device/event_deviceid.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/select_events.hpp>
#include <awl/backends/x11/system/event/opcode.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/unregister/base_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <limits>
#include <fcppt/config/external_end.hpp>


template<
	typename Event
>
sge::x11input::device::event_demuxer<
	Event
>::event_demuxer(
	awl::backends::x11::system::event::processor &_system_processor,
	awl::backends::x11::system::event::opcode const &_opcode,
	awl::backends::x11::window::object const &_window,
	sge::x11input::device::demuxer_enabled const _enabled
)
:
	system_processor_(
		_system_processor
	),
	opcode_(
		_opcode
	),
	window_(
		_window
	),
	connections_(),
	signals_(),
	active_(
		_enabled.get()
	)
{
}

template<
	typename Event
>
sge::x11input::device::event_demuxer<
	Event
>::~event_demuxer()
{
	FCPPT_ASSERT_ERROR(
		signals_.empty()
	);

	FCPPT_ASSERT_ERROR(
		connections_.empty()
	);
}

template<
	typename Event
>
fcppt::signal::auto_connection
sge::x11input::device::event_demuxer<
	Event
>::register_callback(
	awl::backends::x11::system::event::type const &_type,
	sge::x11input::device::id const &_id,
	callback const &_callback
)
{
	if(
		connections_.find(
			_type
		)
		== connections_.end()
	)
		fcppt::container::ptr::insert_unique_ptr_map(
			connections_,
			_type,
			system_processor_.register_callback(
				opcode_,
				_type,
				std::bind(
					&event_demuxer::on_event,
					this,
					std::placeholders::_1
				)
			)
		);

	event_pair const pair(
		_type,
		_id
	);

	typename signal_map::iterator it(
		signals_.find(
			pair
		)
	);

	if(
		it == signals_.end()
	)
	{
		it =
			fcppt::container::ptr::insert_unique_ptr_map(
				signals_,
				pair,
				fcppt::make_unique_ptr<
					signal
				>()
			).first;

		sge::x11input::device::select_events(
			window_,
			_id,
			_type,
			true
		);
	}

	return
		it->second->connect(
			_callback,
			std::bind(
				&event_demuxer::unregister,
				this,
				_id,
				_type
			)
		);
}

template<
	typename Event
>
void
sge::x11input::device::event_demuxer<
	Event
>::active(
	bool const _active
)
{
	active_ = _active;
}

template<
	typename Event
>
void
sge::x11input::device::event_demuxer<
	Event
>::on_event(
	awl::backends::x11::system::event::object const &_event
)
{
	// Ingore everything while not in our window
	if(
		!active_
	)
		return;

	sge::x11input::device::event_data const cookie(
		window_.display(),
		_event
	);

	typedef typename Event::value_type xi_event;

	xi_event const &device_event(
		*fcppt::cast::from_void_ptr<
			xi_event const *
		>(
			cookie.data()
		)
	);

	signals_[
		event_pair(
			awl::backends::x11::system::event::type(
				device_event.evtype
			),
			sge::x11input::device::event_deviceid(
				device_event
			)
		)
	](
		Event(
			device_event
		)
	);
}

template<
	typename Event
>
void
sge::x11input::device::event_demuxer<
	Event
>::unregister(
	sge::x11input::device::id const &_id,
	awl::backends::x11::system::event::type const _type
)
{
	typename signal_map::iterator const it(
		signals_.find(
			event_pair(
				_type,
				_id
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		it
		!= signals_.end()
	);

	if(
		it->second->empty()
	)
	{
		signals_.erase(
			it
		);

		sge::x11input::device::select_events(
			window_,
			_id,
			_type,
			false
		);

		if(
			!this->signal_remains(
				_type
			)
		)
			FCPPT_ASSERT_ERROR(
				connections_.erase(
					_type
				)
				== 1u
			);
	}
}

template<
	typename Event
>
bool
sge::x11input::device::event_demuxer<
	Event
>::signal_remains(
	awl::backends::x11::system::event::type const _type
) const
{
	return
		signals_.lower_bound(
			event_pair(
				_type,
				sge::x11input::device::id(
					std::numeric_limits<
						x11input::device::id::value_type
					>::min()
				)
			)
		)
		!= signals_.upper_bound(
			event_pair(
				_type,
				sge::x11input::device::id(
					std::numeric_limits<
						x11input::device::id::value_type
					>::max()
				)
			)
		);
}

#endif
