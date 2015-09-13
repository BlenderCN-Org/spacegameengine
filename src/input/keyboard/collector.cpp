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


#include <sge/input/processor.hpp>
#include <sge/input/keyboard/char_callback.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event_fwd.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_callback.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/input/keyboard/manager.hpp>
#include <sge/input/keyboard/mod_state.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event_fwd.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/container/bitfield/operators.hpp>
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
sge::input::keyboard::collector::collector(
	sge::input::processor &_processor
)
:
	manager_(
		_processor,
		sge::input::keyboard::discover_callback{
			[](
				sge::input::keyboard::discover_event const &
			){}
		},
		sge::input::keyboard::remove_callback{
			[](
				sge::input::keyboard::remove_event const &
			){}
		},
		sge::input::keyboard::manager::char_callback{
			std::bind(
				&sge::input::keyboard::collector::char_callback_internal,
				this,
				std::placeholders::_1,
				std::placeholders::_2
			)
		},
		sge::input::keyboard::manager::key_callback{
			std::bind(
				&sge::input::keyboard::collector::key_callback_internal,
				this,
				std::placeholders::_1,
				std::placeholders::_2
			)
		},
		sge::input::keyboard::manager::key_repeat_callback{
			std::bind(
				&sge::input::keyboard::collector::key_repeat_callback_internal,
				this,
				std::placeholders::_1,
				std::placeholders::_2
			)
		}
	),
	char_signal_(),
	key_signal_(),
	key_repeat_signal_()
{
}
FCPPT_PP_POP_WARNING

sge::input::keyboard::collector::~collector()
{
}

fcppt::signal::auto_connection
sge::input::keyboard::collector::char_callback(
	sge::input::keyboard::char_callback const &_callback
)
{
	return
		char_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::keyboard::collector::key_callback(
	sge::input::keyboard::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::keyboard::collector::key_repeat_callback(
	sge::input::keyboard::key_repeat_callback const &_callback
)
{
	return
		key_repeat_signal_.connect(
			_callback
		);
}

sge::input::keyboard::mod_state const
sge::input::keyboard::collector::mod_state() const
{
	return
		fcppt::algorithm::fold(
			manager_.devices(),
			sge::input::keyboard::mod_state::null(),
			[](
				sge::input::keyboard::manager::keyboard_map::value_type const &_keyboard,
				sge::input::keyboard::mod_state const &_cur
			)
			{
				return
					_keyboard.first->mod_state()
					|
					_cur;
			}
		);
}

void
sge::input::keyboard::collector::char_callback_internal(
	sge::input::keyboard::device &,
	sge::input::keyboard::char_event const &_event
)
{
	char_signal_(
		_event
	);
}

void
sge::input::keyboard::collector::key_callback_internal(
	sge::input::keyboard::device &,
	sge::input::keyboard::key_event const &_event
)
{
	key_signal_(
		_event
	);
}

void
sge::input::keyboard::collector::key_repeat_callback_internal(
	sge::input::keyboard::device &,
	sge::input::keyboard::key_repeat_event const &_event
)
{
	key_repeat_signal_(
		_event
	);
}
