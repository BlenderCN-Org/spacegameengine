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


#include <sge/audio/player.hpp>
#include <sge/audio/player_plugin/collection_fwd.hpp>
#include <sge/audio/player_plugin/traits.hpp>
#include <sge/log/option_container.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/src/systems/find_plugin.hpp>
#include <sge/src/systems/find_plugin_opt.hpp>
#include <sge/src/systems/logger.hpp>
#include <sge/src/systems/modules/audio/find_player_plugin.hpp>
#include <sge/src/systems/modules/audio/player_pair.hpp>
#include <sge/systems/audio_player.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>


sge::systems::modules::audio::player_pair
sge::systems::modules::audio::find_player_plugin(
	sge::audio::player_plugin::collection const &_collection,
	sge::log::option_container const &_log_options,
	sge::systems::audio_player const &_parameters
)
{
	return
		_parameters.name().has_value()
		?
			sge::systems::find_plugin<
				sge::audio::player
			>(
				_collection,
				_log_options,
				_parameters.name(),
				[](
					sge::audio::player const &
				)
				{
					return
						true;
				}
			)
		:
			fcppt::from_optional(
				sge::systems::find_plugin_opt<
					sge::audio::player
				>(
					_collection,
					_log_options,
					[](
						sge::audio::player const &_player
					)
					{
						return
							!_player.is_null();
					}
				),
				[
					&_collection,
					&_log_options,
					&_parameters
				]
				{
					FCPPT_LOG_WARNING(
						sge::systems::logger(),
						fcppt::log::_
							<< FCPPT_TEXT("Unable to load an audio player that is not null.")
							<< FCPPT_TEXT(" Trying to load a null audio player instead.")
					);

					return
						sge::systems::find_plugin<
							sge::audio::player
						>(
							_collection,
							_log_options,
							_parameters.name(),
							[](
								sge::audio::player const &_player
							)
							{
								return
									_player.is_null();
							}
						);
				}
			)
		;
}
