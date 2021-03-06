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


#ifndef SGE_AUDIO_DIRECTION_OBJECT_HPP_INCLUDED
#define SGE_AUDIO_DIRECTION_OBJECT_HPP_INCLUDED

#include <sge/audio/vector.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/audio/direction/forward.hpp>
#include <sge/audio/direction/up.hpp>


namespace sge
{
namespace audio
{
namespace direction
{

class object
{
public:
	SGE_AUDIO_DETAIL_SYMBOL
	object(
		sge::audio::direction::forward const &,
		sge::audio::direction::up const &
	);

	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::vector
	forward() const;

	SGE_AUDIO_DETAIL_SYMBOL
	void
	forward(
		sge::audio::vector const &
	);

	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::vector
	up() const;

	SGE_AUDIO_DETAIL_SYMBOL
	void
	up(
		sge::audio::vector const &
	);
private:
	sge::audio::vector
		forward_,
		up_;
};

}
}
}

#endif
