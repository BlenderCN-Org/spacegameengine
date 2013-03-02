/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/audio/exception.hpp>
#include <sge/audio/direction/object.hpp>
#include <sge/openal/listener.hpp>
#include <sge/openal/check_state.hpp>
//#include <sge/openal/logger.hpp>
#include <sge/openal/al.hpp>
#include <fcppt/text.hpp>
//#include <fcppt/log/headers.hpp>
//#include <fcppt/math/vector/output.hpp>


namespace
{

void listener_fv(
	ALenum const type,
	ALfloat const *const value)
{
	alListenerfv(
		type,
		value
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alListenerfv failed"),
		sge::audio::exception
	)
}

}

sge::openal::listener::listener()
:
	position_(),
	linear_velocity_()
{
}

sge::openal::listener::~listener()
{
}

void
sge::openal::listener::linear_velocity(
	sge::audio::vector const &n)
{
/*
	FCPPT_LOG_DEBUG(
		sge::openal::logger(),
		fcppt::log::_ << FCPPT_TEXT("setting listener velocity to ") << n);*/

	linear_velocity_ =
		n;

	// TODO: use sge::fcppt::math::vector!
	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};

	listener_fv(
		AL_VELOCITY,
		vec);
}

void
sge::openal::listener::position(
	audio::vector const &n)
{
	/*
	FCPPT_LOG_DEBUG(
		sge::openal::logger(),
		fcppt::log::_ << FCPPT_TEXT("setting listener position to ") << n);
*/

	position_ = n;
	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};
	listener_fv(
		AL_POSITION,
		vec
	);
}

void
sge::openal::listener::direction(
	audio::direction::object const &n)
{
	ALfloat const vec[6] =
		{
			static_cast<ALfloat>(n.forward().x()),
			static_cast<ALfloat>(n.forward().y()),
			static_cast<ALfloat>(n.forward().z()),
			static_cast<ALfloat>(n.up().x()),
			static_cast<ALfloat>(n.up().y()),
			static_cast<ALfloat>(n.up().z())
		};

	listener_fv(
		AL_POSITION,
		vec
	);
}
