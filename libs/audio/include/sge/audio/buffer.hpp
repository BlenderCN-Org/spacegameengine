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


#ifndef SGE_AUDIO_BUFFER_HPP_INCLUDED
#define SGE_AUDIO_BUFFER_HPP_INCLUDED

#include <sge/audio/detail/symbol.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio
{

/// Interface class for buffers (nonstreaming sound factories)
/**
 * The buffer class is an interface class, you cannot instantiate it. Audio
 * plugins (OpenAL, DirectSound) must derive from this class and create
 * instances when a buffer is created via sge::audio::player::create_buffer.
 *
 * For a short introduction to buffers, see \ref audio_overview and
 * \ref audio_example.
 */
class SGE_CORE_DETAIL_CLASS_SYMBOL buffer
{
	FCPPT_NONCOPYABLE(
		buffer
	);
public:
	/// Create a positional sound
	/**
	 * For an introduction to positional (3D) sounds, see \ref audio_positional
	 */
	virtual
	sge::audio::sound::positional_unique_ptr
	create_positional(
		sge::audio::sound::positional_parameters const &
	) = 0;

	/// Create a nonpositional sound
	/**
	 * For an introduction to nonpositional sounds, see \ref audio_example
	 */
	virtual
	sge::audio::sound::base_unique_ptr
	create_nonpositional(
		sge::audio::sound::nonpositional_parameters const &
	) = 0;

	SGE_AUDIO_DETAIL_SYMBOL
	virtual
	~buffer();
protected:
	SGE_AUDIO_DETAIL_SYMBOL
	buffer();
};

}
}

#endif
