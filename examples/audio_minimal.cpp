/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/load_exn.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/direction/object.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/config/media_path.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#ifdef SGE_EXAMPLES_AUDIO_MINIMAL_USE_SYSTEMS_INIT
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#else
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/object.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/audio/player_unique_ptr.hpp>
#include <sge/audio/player_plugin/collection_fwd.hpp>
#include <sge/audio/player_plugin/object.hpp>
#include <sge/config/plugin_path.hpp>
#endif // SGE_EXAMPLES_AUDIO_MINIMAL_USE_SYSTEMS_INIT
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/multi_loader_parameters.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int main()
try
{
	sge::media::extension_set extensions;
	extensions.insert(
		sge::media::extension(
			FCPPT_TEXT("wav")));
#ifdef SGE_EXAMPLES_AUDIO_MINIMAL_USE_SYSTEMS_INIT
//! [systems_initialization]
	// Which file types do we want to load (see below)?

	sge::systems::instance sys(
		sge::systems::list()
			// Player initialization begin
			(sge::systems::audio_player_default())
			// Player initialization end

			// Loader initialization begin
			(sge::systems::audio_loader(
				extensions))
			// Loader initialization end

			// Other system initializations (renderer, ...) here
			// ...
		);

	sge::audio::player &player =
		sys.audio_player();

	sge::audio::multi_loader &loader =
		sys.audio_loader();
//! [systems_initialization]

	/*
//! [systems_null_initialization]
	sge::systems::instance sys(
		sge::systems::list()
			// Player initialization begin
			(sge::systems::audio_player(
//! [systems_null_initialization]
	*/
#else

//! [manual_initialization_pm]
	sge::plugin::manager plugin_manager(
		sge::config::plugin_path(),
		sge::plugin::optional_cache_ref());
//! [manual_initialization_pm]
//
//! [manual_initialization_player]
	sge::audio::player_plugin::collection const audio_players(
		plugin_manager.collection<sge::audio::player>());

	sge::audio::player_plugin::object const player_plugin(
		audio_players.get(0u).load());

	sge::audio::player_unique_ptr const _player(
		player_plugin.get()());

	sge::audio::player &player =
		*_player;
//! [manual_initialization_player]

//! [manual_initialization_loader]
	sge::audio::multi_loader loader(
		sge::audio::multi_loader_parameters(
			plugin_manager.collection<
				sge::audio::loader
			>(),
			sge::media::optional_extension_set(
				extensions
			)
		)
	);
//! [manual_initialization_loader]
#endif

//! [create_file_buffer_and_sound]
	sge::audio::file_unique_ptr const soundfile(
		sge::audio::load_exn(
			loader,
			sge::config::media_path()
				/ FCPPT_TEXT("sounds")
				/ FCPPT_TEXT("ding.wav")));

	sge::audio::buffer_unique_ptr const buf(
		player.create_buffer(
			*soundfile));

	sge::audio::sound::base_unique_ptr const sound(
		buf->create_nonpositional(
			sge::audio::sound::nonpositional_parameters()
				.gain(
					fcppt::literal<
						sge::audio::scalar
					>(
						1
					)
				)
				.pitch(
					fcppt::literal<
						sge::audio::scalar
					>(
						1
					)
				)
			)
		);
//! [create_file_buffer_and_sound]

//! [play]
	sound->play(
		sge::audio::sound::repeat::once);

	while (sound->status() != sge::audio::sound::play_status::stopped)
		sound->update();
//! [play]

//! [listener_direction]
	player.listener().position(
		sge::audio::vector(
			0.0f,
			0.0f,
			0.0f));

	player.listener().linear_velocity(
		sge::audio::vector(
			0.0f,
			0.0f,
			0.0f));

	player.listener().direction(
		sge::audio::direction::object(
			sge::audio::direction::forward(
				sge::audio::vector(
					0.0f,
					0.0f,
					1.0f)),
			sge::audio::direction::up(
				sge::audio::vector(
					0.0f,
					1.0f,
					0.0f))));
//! [listener_direction]

//! [create_and_play_streaming]
	sge::audio::sound::base_unique_ptr const streaming(
		player.create_nonpositional_stream(
			*soundfile,
			sge::audio::sound::nonpositional_parameters()));

	while (streaming->status() != sge::audio::sound::play_status::stopped)
		streaming->update();
//! [create_and_play_streaming]
}
catch(
	fcppt::exception const &_error)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
