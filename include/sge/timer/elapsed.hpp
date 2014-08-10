/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_TIMER_ELAPSED_HPP_INCLUDED
#define SGE_TIMER_ELAPSED_HPP_INCLUDED

#include <sge/timer/basic.hpp>
#include <sge/timer/interval.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace timer
{

template<
	typename Duration,
	typename Clock
>
Duration const
elapsed(
	sge::timer::basic<
		Clock
	> const &_timer
)
{
	if(
		!_timer.active()
	)
		return
			Duration();

	if(
		_timer.expired()
	)
		return
			sge::timer::interval<
				Duration
			>(
				_timer
			);

	return
		std::chrono::duration_cast<
			Duration
		>(
			_timer.now() -
			_timer.last_time()
		);
}

}
}

#endif
