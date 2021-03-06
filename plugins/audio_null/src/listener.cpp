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


#include <sge/audio/vector_fwd.hpp>
#include <sge/audio/direction/object.hpp>
#include <sge/audio_null/listener.hpp>


sge::audio_null::listener::listener()
{
}

sge::audio_null::listener::~listener()
{
}

void
sge::audio_null::listener::position(
	sge::audio::vector const &
)
{
}

void
sge::audio_null::listener::linear_velocity(
	sge::audio::vector const &
)
{
}

void
sge::audio_null::listener::direction(
	sge::audio::direction::object const &
)
{
}
