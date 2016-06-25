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


#include <sge/input/processor.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/manager.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::input::keyboard::manager::manager(
	sge::input::processor &_processor,
	sge::input::keyboard::discover_callback const &_discover_callback,
	sge::input::keyboard::remove_callback const &_remove_callback,
	key_callback const &_key_callback
)
:
	devices_(),
	discover_callback_(
		_discover_callback
	),
	remove_callback_(
		_remove_callback
	),
	key_callback_(
		_key_callback
	),
	discover_connection_(
		_processor.keyboard_discover_callback(
			sge::input::keyboard::discover_callback{
				std::bind(
					&sge::input::keyboard::manager::discover,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	remove_connection_(
		_processor.keyboard_remove_callback(
			sge::input::keyboard::remove_callback{
				std::bind(
					&sge::input::keyboard::manager::remove,
					this,
					std::placeholders::_1
				)
			}
		)
	)
{
}
FCPPT_PP_POP_WARNING

sge::input::keyboard::manager::~manager()
{
}

sge::input::keyboard::manager::keyboard_map const &
sge::input::keyboard::manager::devices() const
{
	return
		devices_;
}

void
sge::input::keyboard::manager::discover(
	sge::input::keyboard::discover_event const &_event
)
{
	FCPPT_ASSERT_ERROR(
		devices_.insert(
			std::make_pair(
				fcppt::make_ref(
					_event.get()
				),
				fcppt::assign::make_container<
					fcppt::signal::auto_connection_container
				>(
					_event.get().key_callback(
						sge::input::keyboard::key_callback{
							std::bind(
								key_callback_,
								std::ref(
									_event.get()
								),
								std::placeholders::_1
							)
						}
					)
				)
			)
		).second
	);

	discover_callback_(
		_event
	);
}

void
sge::input::keyboard::manager::remove(
	sge::input::keyboard::remove_event const &_event
)
{
	FCPPT_ASSERT_ERROR(
		devices_.erase(
			fcppt::make_ref(
				_event.get()
			)
		)
		== 1u
	);

	remove_callback_(
		_event
	);
}
