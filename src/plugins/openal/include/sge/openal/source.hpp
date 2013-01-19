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


#ifndef SGE_OPENAL_SOURCE_HPP_INCLUDED
#define SGE_OPENAL_SOURCE_HPP_INCLUDED

#include <sge/openal/openal.hpp>
#include <sge/openal/source_wrapper.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/vector_fwd.hpp>
#include <sge/audio/sound/optional_direction_fwd.hpp>
#include <sge/audio/sound/play_status_fwd.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace openal
{
class source
:
	public audio::sound::positional
{
	FCPPT_NONCOPYABLE(
		source
	);
public:
	explicit
	source(
		audio::sound::nonpositional_parameters const &,
		ALuint buffer);

	explicit
	source(
		audio::sound::positional_parameters const &,
		ALuint buffer);

	explicit
	source(
		audio::sound::nonpositional_parameters const &);

	explicit
	source(
		audio::sound::positional_parameters const &);

	~source();

	void
	play(
		audio::sound::repeat);

	void
	toggle_pause();

	sge::audio::sound::play_status
	status() const;

	void
	stop();

	void
	update();

	void
	position(
		audio::vector const &);

	void
	linear_velocity(
		audio::vector const &);

	void
	gain(
		audio::scalar);

	void
	pitch(
		audio::scalar);

	void
	rolloff_factor(
		audio::scalar);

	void
	reference_distance(
		audio::scalar);

	void
	max_distance(
		audio::scalar);

	void
	direction(
		audio::sound::optional_direction const &);

	void
	inner_cone_angle(
		audio::scalar);

	void
	outer_cone_angle(
		audio::scalar);

	void
	outer_cone_gain(
		audio::scalar);
protected:
	virtual void
	do_play();

	ALuint
	source_id() const;

	audio::sound::repeat
	repeat() const;
private:
	source_wrapper source_;
	audio::sound::repeat repeat_;

	void
	init(
		audio::sound::positional_parameters const &);

	void
	init(
		audio::sound::nonpositional_parameters const &);
};
}
}

#endif
