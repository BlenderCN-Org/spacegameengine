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


#ifndef SGE_TIMER_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_TIMER_PARAMETERS_DECL_HPP_INCLUDED

#include <sge/timer/parameters_fwd.hpp>
#include <sge/timer/clocks/detail/wrapper.hpp>


namespace sge
{
namespace timer
{

template<
	typename Clock
>
class parameters final
:
	sge::timer::clocks::detail::wrapper<
		Clock
	>
{
	typedef
	sge::timer::clocks::detail::wrapper<
		Clock
	>
	state_base;
public:
	typedef
	Clock
	clock_type;

	typedef
	typename
	clock_type::duration
	duration;

	explicit
	parameters(
		duration
	);

	parameters(
		clock_type const &,
		duration
	);

	parameters &
	active(
		bool
	);

	parameters &
	expired(
		bool
	);

	duration
	interval() const;

	state_base const &
	clock() const;

	bool
	active() const;

	bool
	expired() const;
private:
	duration interval_;

	bool active_;

	bool expired_;
};

}
}

#endif
