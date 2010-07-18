/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/audio/pool.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/log/global.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert_message.hpp>
#include <boost/foreach.hpp>

sge::audio::pool::pool()
{}

void
sge::audio::pool::add(
	sound::base_ptr const s,
	stop_mode::type const pm
)
{
	sounds.push_back(
		value_type(
			s,
			pm));
}

void
sge::audio::pool::update()
{
	for (container_type::iterator s = sounds.begin();
	     s != sounds.end();)
	{
		// sound's not dead yet?
		if (!s->first.unique())
		{
			s->first->update();
			s++;
			continue;
		}

		switch (s->second)
		{
			case stop_mode::stop_playing:
			break;
			case stop_mode::continue_playing:
				FCPPT_ASSERT_MESSAGE(
					s->first->status() != audio::sound::play_status::paused,
					FCPPT_TEXT("a paused sound was destroyed but kept alive by the sound pool")
				);

				if (s->first->status() != audio::sound::play_status::stopped)
				{
					s++;
					continue;
				}
			break;
			case stop_mode::play_once:
				FCPPT_ASSERT_MESSAGE(
					s->first->status() != audio::sound::play_status::paused,
					FCPPT_TEXT("a paused sound was destroyed but kept alive by the sound pool")
				);

				if (s->first->status() != audio::sound::play_status::stopped)
				{
					if (s->first->repeat() != sound::repeat::once)
					{
						FCPPT_LOG_WARNING(
							log::global(),
							fcppt::log::_
								<< FCPPT_TEXT("got a looping sound, setting to play only once")
						);

						s->first->play(sound::repeat::once);
					}
					s++;
					continue;
				}
			break;
		}

		s = sounds.erase(s);
	}
}

bool
sge::audio::pool::sounds_finished() const
{
	BOOST_FOREACH(
		value_type const &s,
		sounds
	)
		if (s.first->status() != audio::sound::play_status::stopped)
			return false;
	return true;
}
