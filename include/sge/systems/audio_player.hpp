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


#ifndef SGE_SYSTEMS_AUDIO_PLAYER_HPP_INCLUDED
#define SGE_SYSTEMS_AUDIO_PLAYER_HPP_INCLUDED

#include <sge/audio/player_capabilities_field.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/symbol.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>


namespace sge
{
namespace systems
{

class audio_player
{
	FCPPT_NONASSIGNABLE(
		audio_player
	);
public:
	SGE_SYSTEMS_SYMBOL
	explicit
	audio_player(
		audio::player_capabilities_field const &
	);

	SGE_SYSTEMS_SYMBOL
	audio::player_capabilities_field const &
	capabilities() const;
private:
	audio::player_capabilities_field const capabilities_;
};

}
}

#endif
