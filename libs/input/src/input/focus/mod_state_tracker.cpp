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


#include <sge/input/focus/count.hpp>
#include <sge/input/focus/in_callback.hpp>
#include <sge/input/focus/in_event.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_event.hpp>
#include <sge/input/focus/mod_state_tracker.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/key/mod_state.hpp>
#include <sge/input/key/modifier.hpp>
#include <sge/input/key/to_modifier.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/algorithm/enum_array_init.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/cast/to_void.hpp>
#include <fcppt/container/enum_array_impl.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::input::focus::mod_state_tracker::mod_state_tracker(
	sge::input::focus::object &_focus
)
:
	counts_(
		sge::input::focus::mod_state_tracker::null_array()
	),
	in_connection_(
		_focus.in_callback(
			sge::input::focus::in_callback(
				[
					this
				](
					sge::input::focus::in_event const &
				)
				{
					counts_ =
						sge::input::focus::mod_state_tracker::null_array();
				}
			)
		)
	),
	key_connection_(
		_focus.key_callback(
			sge::input::focus::key_callback(
				[
					this
				](
					sge::input::focus::key_event const &_event
				)
				{
					fcppt::optional::maybe_void(
						sge::input::key::to_modifier(
							_event.key().code()
						),
						[
							&_event,
							this
						](
							sge::input::key::modifier const _mod
						)
						{
							count &entry(
								counts_[
									_mod
								]
							);

							if(
								_event.pressed()
							)
								++entry;
							else if(
								entry
								!=
								sge::input::focus::count{
									0u
								}
							)
								--entry;
						}
					);
				}
			)
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::input::focus::mod_state_tracker::~mod_state_tracker()
{
}

sge::input::key::mod_state
sge::input::focus::mod_state_tracker::mod_state() const
{
	return
		fcppt::algorithm::fold(
			fcppt::make_enum_range<
				sge::input::key::modifier
			>(),
			sge::input::key::mod_state::null(),
			[
				this
			](
				sge::input::key::modifier const _mod,
				sge::input::key::mod_state const _state
			)
			{
				return
					counts_[
						_mod
					]
					!=
					sge::input::focus::count{
						0u
					}
					?
						_state
						|
						_mod
					:
						_state
					;
			}
		);
}

sge::input::focus::mod_state_tracker::count_array
sge::input::focus::mod_state_tracker::null_array()
{
	return
		fcppt::algorithm::enum_array_init<
			count_array
		>(
			[](
				auto const _index
			)
			{
				fcppt::cast::to_void(
					_index
				);

				return
					sge::input::focus::count{
						0u
					};
			}
		);
}
