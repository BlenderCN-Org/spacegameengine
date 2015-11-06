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


#ifndef SGE_AUDIO_SOUND_NONPOSITIONAL_PARAMETERS_HPP_INCLUDED
#define SGE_AUDIO_SOUND_NONPOSITIONAL_PARAMETERS_HPP_INCLUDED

#include <sge/audio/scalar.hpp>
#include <sge/audio/detail/symbol.hpp>


namespace sge
{
namespace audio
{
namespace sound
{

/// Holds all the data necessary to construct a nonpositional sound
class nonpositional_parameters
{
public:
	SGE_AUDIO_DETAIL_SYMBOL
	nonpositional_parameters();

	/// Get the gain
	/** \see sge::audio::sound::base::gain */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::scalar
	gain() const;

	/// Set the gain
	/** \see sge::audio::sound::base::gain */
	SGE_AUDIO_DETAIL_SYMBOL
	nonpositional_parameters &
	gain(
		sge::audio::scalar
	);

	/// Get the pitch
	/** \see sge::audio::sound::base::pitch */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::scalar
	pitch() const;

	/// Set the pitch
	/** \see sge::audio::sound::base::pitch */
	SGE_AUDIO_DETAIL_SYMBOL
	nonpositional_parameters &
	pitch(
		sge::audio::scalar
	);
private:
	sge::audio::scalar gain_;

	sge::audio::scalar pitch_;
};

}
}
}

#endif
