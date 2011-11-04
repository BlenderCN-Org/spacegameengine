/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/audio/sound/positional_parameters.hpp>

sge::audio::sound::positional_parameters::positional_parameters()
:
	position_(
		audio::vector::null()),
	linear_velocity_(
		audio::vector::null()),
	gain_(
		static_cast<audio::scalar>(
			1)),
	pitch_(
		static_cast<audio::scalar>(
			1)),
	rolloff_(
		static_cast<audio::scalar>(
			1)),
	// setting the direction vector to zero creates a non-directional source.
	// this, of course, assumes that the zero vector is uniquely identified by
	// (0.0f,0.0f,0.0f) which is not really guaranteed
	direction_(
		audio::vector::null()),
	inner_cone_angle_(
		static_cast<audio::scalar>(
			360)),
	outer_cone_angle_(
		static_cast<audio::scalar>(
			360)),
	outer_cone_gain_(
		static_cast<audio::scalar>(
			1))
{
}

sge::audio::vector const &
sge::audio::sound::positional_parameters::position() const
{
	return position_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::position(
	sge::audio::vector const &_position)
{
	position_ = _position;
	return *this;
}

sge::audio::vector const &
sge::audio::sound::positional_parameters::linear_velocity() const
{
	return linear_velocity_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::linear_velocity(
	sge::audio::vector const &_linear_velocity)
{
	linear_velocity_ = _linear_velocity;
	return *this;
}

sge::audio::scalar const &
sge::audio::sound::positional_parameters::pitch() const
{
	return pitch_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::pitch(
	sge::audio::scalar const &_pitch)
{
	pitch_ = _pitch;
	return *this;
}

sge::audio::scalar const &
sge::audio::sound::positional_parameters::gain() const
{
	return gain_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::gain(
	sge::audio::scalar const &_gain)
{
	gain_ = _gain;
	return *this;
}

sge::audio::scalar const &
sge::audio::sound::positional_parameters::rolloff() const
{
	return rolloff_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::rolloff(
	sge::audio::scalar const &_rolloff)
{
	rolloff_ = _rolloff;
	return *this;
}

sge::audio::vector const &
sge::audio::sound::positional_parameters::direction() const
{
	return direction_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::direction(
	sge::audio::vector const &_direction)
{
	direction_ = _direction;
	return *this;
}

sge::audio::scalar const &
sge::audio::sound::positional_parameters::inner_cone_angle() const
{
	return inner_cone_angle_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::inner_cone_angle(
	sge::audio::scalar const &_inner_cone_angle)
{
	inner_cone_angle_ = _inner_cone_angle;
	return *this;
}

sge::audio::scalar const &
sge::audio::sound::positional_parameters::outer_cone_angle() const
{
	return outer_cone_angle_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::outer_cone_angle(
	sge::audio::scalar const &_outer_cone_angle)
{
	outer_cone_angle_ = _outer_cone_angle;
	return *this;
}

sge::audio::scalar const &
sge::audio::sound::positional_parameters::outer_cone_gain() const
{
	return outer_cone_gain_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::outer_cone_gain(
	sge::audio::scalar const &_outer_cone_gain)
{
	outer_cone_gain_ = _outer_cone_gain;
	return *this;
}
