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


#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/mod_state.hpp>
#include <sge/input/keyboard/modifier.hpp>
#include <sge/input/keyboard/to_modifier.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/window_demuxer.hpp>
#include <sge/x11input/device/window_event.hpp>
#include <sge/x11input/keyboard/device.hpp>
#include <sge/x11input/keyboard/fake_core_event.hpp>
#include <sge/x11input/keyboard/key_code_to_key_sym.hpp>
#include <sge/x11input/keyboard/key_id.hpp>
#include <sge/x11input/keyboard/looked_up_string.hpp>
#include <sge/x11input/keyboard/lookup_string.hpp>
#include <sge/x11input/keyboard/translate_key_code.hpp>
#include <awl/backends/x11/system/event/object.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::x11input::keyboard::device::device(
	sge::x11input::device::parameters const &_param,
	sge::x11input::input_context const &_input_context
)
:
	sge::input::keyboard::device(),
	sge::x11input::device::object(
		_param.id()
	),
	window_(
		_param.window()
	),
	input_context_(_input_context),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
				XI_KeyPress
				),
				_param.id(),
				std::bind(
					&sge::x11input::keyboard::device::on_key_press,
					this,
					std::placeholders::_1
				)
			)
		)
		(
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_KeyRelease
				),
				_param.id(),
				std::bind(
					&sge::x11input::keyboard::device::on_key_release,
					this,
					std::placeholders::_1
				)
			)
		)
		.move_container()
	),
	key_signal_(),
	key_repeat_signal_(),
	char_signal_(),
	modifiers_(
		sge::input::keyboard::mod_state::null()
	)
{
}

sge::x11input::keyboard::device::~device()
{
}

fcppt::signal::auto_connection
sge::x11input::keyboard::device::key_callback(
	sge::input::keyboard::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::keyboard::device::key_repeat_callback(
	sge::input::keyboard::key_repeat_callback const &_callback
)
{
	return
		key_repeat_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::keyboard::device::char_callback(
	sge::input::keyboard::char_callback const &_callback
)
{
	return
		char_signal_.connect(
			_callback
		);
}

sge::input::keyboard::mod_state const
sge::x11input::keyboard::device::mod_state() const
{
	return
		modifiers_;
}

void
sge::x11input::keyboard::device::on_key_press(
	sge::x11input::device::window_event const &_event
)
{
	sge::x11input::keyboard::fake_core_event(
		window_,
		_event
	);

	sge::x11input::keyboard::looked_up_string const lookup(
		sge::x11input::keyboard::lookup_string(
			input_context_,
			_event.get()
		)
	);

	sge::input::keyboard::key const key(
		lookup.key_code(),
		sge::x11input::keyboard::key_id(
			_event
		)
	);

	bool const is_repeated(
		_event.get().flags & XIKeyRepeat
	);

	if(
		is_repeated
	)
		key_repeat_signal_(
			sge::input::keyboard::key_repeat_event(
				key
			)
		);
	else
	{
		this->update_modifiers(
			lookup.key_code(),
			true
		);

		key_signal_(
			sge::input::keyboard::key_event(
				key,
				true
			)
		);
	}

	sge::x11input::keyboard::char_vector const &char_codes(
		lookup.char_codes()
	);

	for(
		auto const &element
		:
		char_codes
	)
		char_signal_(
			sge::input::keyboard::char_event(
				element,
				is_repeated
			)
		);
}

void
sge::x11input::keyboard::device::on_key_release(
	sge::x11input::device::window_event const &_event
)
{
	sge::x11input::keyboard::fake_core_event(
		window_,
		_event
	);

	sge::input::keyboard::key_code const key_code(
		sge::x11input::keyboard::translate_key_code(
			sge::x11input::keyboard::key_code_to_key_sym(
				window_.display(),
				_event.get().detail
			)
		)
	);

	this->update_modifiers(
		key_code,
		false
	);

	key_signal_(
		sge::input::keyboard::key_event(
			sge::input::keyboard::key{
				key_code,
				sge::x11input::keyboard::key_id(
					_event
				)
			},
			false
		)
	);
}

void
sge::x11input::keyboard::device::update_modifiers(
	sge::input::keyboard::key_code const _key_code,
	bool const _pressed
)
{
	fcppt::maybe_void(
		sge::input::keyboard::to_modifier(
			_key_code
		),
		[
			this,
			_pressed
		](
			sge::input::keyboard::modifier const &_mod
		)
		{
			modifiers_[
				_mod
			] = _pressed;
		}
	);
}
