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


#include <sge/time/timer.hpp>
#include <sge/time/resolution.hpp>

sge::time::timer::timer(
	resolution const &res_,
	activation_state::type const active_,
	fun const &fun_,
	expiration_state::type const expired_)
:
	fun_(fun_),
	interval_(res_.get()),
	last_time_(fun_()),
	active_(active_),
	expired_(expired_)
{}

sge::time::timer::frames_type
sge::time::timer::update()
{
	frames_type const f = elapsed_frames();
	if(f >= static_cast<frames_type>(1))
		reset();
	return f < static_cast<frames_type>(1)
		? static_cast<frames_type>(0)
		: f;
}

bool sge::time::timer::update_b()
{
	if(!expired())
		return false;
	reset();
	return true;
}

sge::time::timer::frames_type
sge::time::timer::elapsed_frames() const
{
	if(!active())
		return static_cast<frames_type>(0);

	if(expired_ == expiration_state::expired)
		return static_cast<frames_type>(1);
	
	return static_cast<frames_type>(fun_() - last_time())
		/ static_cast<frames_type>(interval());
}

sge::time::timer::frames_type
sge::time::timer::reset()
{
	frames_type const f = elapsed_frames();
	last_time_ = fun_();
	expired_ = expiration_state::not_expired;
	return f;
}

bool sge::time::timer::expired() const
{
	return
		active()
		&& (expired_ == expiration_state::expired
		|| elapsed_frames() >= 1);
}

void  sge::time::timer::activate()
{
	if(active())
		return;
	reset();
	active_ = activation_state::active;
}

void sge::time::timer::deactivate()
{
	active_ = activation_state::inactive;
}

sge::time::timer::interval_type
sge::time::timer::interval() const
{
	return interval_;
}

sge::time::timer::interval_type
sge::time::timer::last_time() const
{
	return last_time_;
}

bool sge::time::timer::active() const
{
	return active_ == activation_state::active;
}

void sge::time::timer::interval(
	resolution const &i)
{
	interval_ = i.get();
	reset();
}

void sge::time::timer::expire()
{
	expired_ = expiration_state::expired;
}
