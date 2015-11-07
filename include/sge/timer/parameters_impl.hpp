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


#ifndef SGE_TIMER_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_TIMER_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/timer/parameters_decl.hpp>
#include <sge/timer/clocks/is_stateful.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


template<
	typename Clock
>
template<
	typename Rep,
	typename Period
>
sge::timer::parameters<
	Clock
>::parameters(
	std::chrono::duration<
		Rep,
		Period
	> const _interval
)
:
	parameters(
		clock_type(),
		_interval
	)
{
	static_assert(
		!sge::timer::clocks::is_stateful<
			Clock
		>::value,
		"Stateful clocks need to be passed as parameters"
	);
}

template<
	typename Clock
>
template<
	typename Rep,
	typename Period
>
sge::timer::parameters<
	Clock
>::parameters(
	clock_type const &_clock,
	std::chrono::duration<
		Rep,
		Period
	> const _interval
)
:
	state_base(
		_clock
	),
	interval_{
		_interval
	},
	active_{
		true
	},
	expired_{
		false
	}
{
}

template<
	typename Clock
>
sge::timer::parameters<
	Clock
> &
sge::timer::parameters<
	Clock
>::active(
	bool const _active
)
{
	active_ =
		_active;

	return
		*this;
}

template<
	typename Clock
>
sge::timer::parameters<
	Clock
> &
sge::timer::parameters<
	Clock
>::expired(
	bool const _expired
)
{
	expired_ =
		_expired;

	return
		*this;
}

template<
	typename Clock
>
typename
sge::timer::parameters<
	Clock
>::duration
sge::timer::parameters<
	Clock
>::interval() const
{
	return
		interval_;
}

template<
	typename Clock
>
typename
sge::timer::parameters<
	Clock
>::state_base const &
sge::timer::parameters<
	Clock
>::clock() const
{
	return
		*this;
}

template<
	typename Clock
>
bool
sge::timer::parameters<
	Clock
>::active() const
{
	return
		active_;
}

template<
	typename Clock
>
bool
sge::timer::parameters<
	Clock
>::expired() const
{
	return
		expired_;
}

#endif
