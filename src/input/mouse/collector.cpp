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


#include <sge/input/processor_fwd.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/mouse/axis_callback.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_callback.hpp>
#include <sge/input/mouse/button_event_fwd.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/collector.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_event_fwd.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/input/mouse/manager.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_event_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::input::mouse::collector::collector(
	sge::input::processor &_processor
)
:
	manager_(
		_processor,
		sge::input::mouse::discover_callback{
			[](
				sge::input::mouse::discover_event const &
			){}
		},
		sge::input::mouse::remove_callback{
			[](
				sge::input::mouse::remove_event const &
			){}
		},
		sge::input::mouse::manager::axis_callback{
			std::bind(
				&sge::input::mouse::collector::axis_callback_internal,
				this,
				std::placeholders::_1,
				std::placeholders::_2
			)
		},
		sge::input::mouse::manager::button_callback{
			std::bind(
				&sge::input::mouse::collector::button_callback_internal,
				this,
				std::placeholders::_1,
				std::placeholders::_2
			)
		}
	),
	info_(
		sge::input::mouse::axis_info_container(
			sge::input::mouse::axis_info_container::vector()
		),
		sge::input::mouse::button_info_container(
			sge::input::mouse::button_info_container::vector()
		),
		sge::input::info::name(
			FCPPT_TEXT("mouse collector")
		)
	),
	axis_signal_(),
	button_signal_()
{
}
FCPPT_PP_POP_WARNING

sge::input::mouse::collector::~collector()
{
}

fcppt::signal::auto_connection
sge::input::mouse::collector::axis_callback(
	sge::input::mouse::axis_callback const &_callback
)
{
	return
		axis_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::mouse::collector::button_callback(
	sge::input::mouse::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

sge::input::mouse::info const &
sge::input::mouse::collector::info() const
{
	return
		info_;
}

void
sge::input::mouse::collector::axis_callback_internal(
	sge::input::mouse::device &,
	sge::input::mouse::axis_event const &_event
)
{
	axis_signal_(
		_event
	);
}

void
sge::input::mouse::collector::button_callback_internal(
	sge::input::mouse::device &,
	sge::input::mouse::button_event const &_event
)
{
	button_signal_(
		_event
	);
}
