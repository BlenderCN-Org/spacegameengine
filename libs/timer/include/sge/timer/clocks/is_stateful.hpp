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


#ifndef SGE_TIMER_CLOCKS_IS_STATEFUL_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_IS_STATEFUL_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace timer
{
namespace clocks
{

template<
	typename Clock,
	typename Enable = void
>
struct is_stateful
:
std::true_type
{
};

template<
	typename Clock
>
struct is_stateful<
	Clock,
	std::enable_if_t<
		std::is_same<
			std::chrono::high_resolution_clock,
			Clock
		>::value
		||
		std::is_same<
			std::chrono::steady_clock,
			Clock
		>::value
		||
		std::is_same<
			std::chrono::system_clock,
			Clock
		>::value
	>
>
:
std::false_type
{
};

}
}
}

#endif
