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


#include <sge/audio/player_ptr.hpp>
#include <sge/audio_null/player.hpp>
#include <sge/plugin/capabilities.hpp>
#include <sge/plugin/capabilities_field.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/min_core_version.hpp>
#include <sge/plugin/version.hpp>
#include <sge/plugin/library/make_interface.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>


namespace
{

sge::plugin::info const info(
	FCPPT_TEXT("audio_null"),
	FCPPT_TEXT("An audio plugin that does not do anything."),
	sge::plugin::version(0x1u),
	sge::plugin::min_core_version(0x1u),
	sge::plugin::capabilities_field(
		sge::plugin::capabilities::audio_player
	)
);

sge::audio::player_ptr const
create_audio_player()
{
	return
		fcppt::make_shared_ptr<
			sge::audio_null::player
		>();
}

}

SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(
	info,
	(create_audio_player)
)
