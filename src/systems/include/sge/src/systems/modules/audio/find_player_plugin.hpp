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


#ifndef SGE_SRC_SYSTEMS_MODULES_AUDIO_FIND_PLAYER_PLUGIN_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_AUDIO_FIND_PLAYER_PLUGIN_HPP_INCLUDED

#include <sge/audio/player_plugin/collection_fwd.hpp>
#include <sge/log/option_container.hpp>
#include <sge/src/systems/modules/audio/player_pair_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>


namespace sge
{
namespace systems
{
namespace modules
{
namespace audio
{

sge::systems::modules::audio::player_pair
find_player_plugin(
	sge::audio::player_plugin::collection const &,
	sge::log::option_container const &,
	sge::systems::audio_player const &
);

}
}
}
}

#endif
