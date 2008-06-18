/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_AUDIO_SOUND_HPP_INCLUDED
#define SGE_AUDIO_SOUND_HPP_INCLUDED

#include "../../math/vector.hpp"

namespace sge
{
namespace audio
{

class sound
{
public:
	enum sound_status 
	{ 
		status_stopped,
		status_playing,
		status_paused 
	};

	virtual void play(const bool) = 0;
	virtual void toggle_pause() = 0;
	virtual sound_status status() const = 0;
	virtual void stop() = 0;
	virtual math::vector3 pos() const = 0;
	virtual void pos(const math::vector3 &) = 0;
	virtual bool positional() const = 0;
	virtual void positional(const bool) = 0;
	virtual void update() {}
	virtual ~sound() {}
};
}
}

#endif // SOUND_HPP
