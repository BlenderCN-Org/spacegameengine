/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_TIMER_CLOCKS_DELTA_IMPL_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_DELTA_IMPL_HPP_INCLUDED

#include <sge/timer/clocks/delta_decl.hpp>
#include <fcppt/chrono/time_point_arithmetic.hpp>
#include <fcppt/chrono/time_point_impl.hpp>


template<typename Impl>
sge::timer::clocks::delta<Impl>::delta()
:
	now_()
{
}

template<typename Impl>
sge::timer::clocks::delta<Impl>::~delta()
{
}

template<typename Impl>
void
sge::timer::clocks::delta<Impl>::update(
	duration const &_delta)
{
	now_ +=
		_delta;
}

template<typename Impl>
typename sge::timer::clocks::delta<Impl>::time_point
sge::timer::clocks::delta<Impl>::now() const
{
	return
		now_;
}

#endif
