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


#include <sge/input/focus/char_callback.hpp>
#include <sge/input/focus/char_event.hpp>
#include <sge/input/focus/in_callback.hpp>
#include <sge/input/focus/in_event.hpp>
#include <sge/input/focus/key.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_event.hpp>
#include <sge/input/focus/key_repeat_callback.hpp>
#include <sge/input/focus/key_repeat_event.hpp>
#include <sge/input/focus/out_callback.hpp>
#include <sge/input/focus/out_event.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/window_demuxer.hpp>
#include <sge/x11input/device/window_event.hpp>
#include <sge/x11input/focus/looked_up_string.hpp>
#include <sge/x11input/focus/lookup_string.hpp>
#include <sge/x11input/focus/object.hpp>
#include <sge/x11input/key/event_to_sge_code.hpp>
#include <sge/x11input/key/repeated.hpp>
#include <sge/x11input/xim/context.hpp>
#include <sge/x11input/xim/method.hpp>
#include <awl/backends/x11/system/event/object.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::x11input::focus::object::object(
	fcppt::log::object &_log,
	sge::x11input::device::parameters const &_param,
	sge::x11input::xim::method const &_xim_method
)
:
	sge::input::focus::object(),
	sge::x11input::device::object(
		_param.id()
	),
	log_{
		_log
	},
	key_signal_(),
	key_repeat_signal_(),
	char_signal_(),
	in_signal_(),
	out_signal_(),
	window_(
		_param.window()
	),
	xim_context_(
		fcppt::make_unique_ptr<
			sge::x11input::xim::context
		>(
			_xim_method.get(),
			_param.window()
		)
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_KeyPress
				),
				_param.id(),
				sge::x11input::device::window_demuxer::callback{
					std::bind(
						&sge::x11input::focus::object::on_key_press,
						this,
						std::placeholders::_1
					)
				}
			),
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_KeyRelease
				),
				_param.id(),
				sge::x11input::device::window_demuxer::callback{
					std::bind(
						&sge::x11input::focus::object::on_key_release,
						this,
						std::placeholders::_1
					)
				}
			),
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_FocusIn
				),
				_param.id(),
				sge::x11input::device::window_demuxer::callback{
					[
						this
					](
						sge::x11input::device::window_event const &
					)
					{
						in_signal_(
							sge::input::focus::in_event{}
						);
					}
				}
			),
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_FocusOut
				),
				_param.id(),
				sge::x11input::device::window_demuxer::callback{
					[
						this
					](
						sge::x11input::device::window_event const &
					)
					{
						out_signal_(
							sge::input::focus::out_event{}
						);
					}
				}
			)
		)
	)
{
}

sge::x11input::focus::object::~object()
{
}

fcppt::signal::auto_connection
sge::x11input::focus::object::key_callback(
	sge::input::focus::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::focus::object::key_repeat_callback(
	sge::input::focus::key_repeat_callback const &_callback
)
{
	return
		key_repeat_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::focus::object::char_callback(
	sge::input::focus::char_callback const &_callback
)
{
	return
		char_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::focus::object::in_callback(
	sge::input::focus::in_callback const &_callback
)
{
	return
		in_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::focus::object::out_callback(
	sge::input::focus::out_callback const &_callback
)
{
	return
		out_signal_.connect(
			_callback
		);
}

void
sge::x11input::focus::object::on_key_press(
	sge::x11input::device::window_event const &_event
)
{
	sge::x11input::focus::looked_up_string const lookup(
		sge::x11input::focus::lookup_string(
			log_,
			*xim_context_,
			_event.get()
		)
	);

	sge::input::focus::key const key(
		lookup.key_code()
	);

	if(
		sge::x11input::key::repeated(
			_event.get()
		)
	)
		key_repeat_signal_(
			sge::input::focus::key_repeat_event(
				key
			)
		);
	else
		key_signal_(
			sge::input::focus::key_event(
				key,
				sge::input::key::pressed{
					true
				}
			)
		);

	for(
		auto const &element
		:
		lookup.char_codes()
	)
		char_signal_(
			sge::input::focus::char_event(
				element
			)
		);
}

void
sge::x11input::focus::object::on_key_release(
	sge::x11input::device::window_event const &_event
)
{
	key_signal_(
		sge::input::focus::key_event(
			sge::input::focus::key{
				sge::x11input::key::event_to_sge_code(
					window_.display(),
					_event.get()
				)
			},
			sge::input::key::pressed{
				false
			}
		)
	);
}
