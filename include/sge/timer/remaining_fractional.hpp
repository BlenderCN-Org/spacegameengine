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


#ifndef SGE_TIMER_REMAINING_FRACTIONAL_HPP_INCLUDED
#define SGE_TIMER_REMAINING_FRACTIONAL_HPP_INCLUDED

#include <sge/timer/basic_fwd.hpp>
#include <sge/timer/elapsed_fractional.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace timer
{

template<
	typename Float,
	typename Clock
>
typename
boost::enable_if<
	std::is_floating_point<
		Float
	>,
	Float
>::type
remaining_fractional(
	sge::timer::basic<
		Clock
	> const &_timer
)
{
	return
		fcppt::literal<
			Float
		>(
			1
		)
		-
		sge::timer::elapsed_fractional<
			Float
		>(
			_timer
		);
}

}
}

#endif
