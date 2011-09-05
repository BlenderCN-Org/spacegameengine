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


#ifndef SGE_TIMER_CLOCKS_IS_STATEFUL_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_IS_STATEFUL_HPP_INCLUDED

#include <fcppt/chrono/high_resolution_clock_fwd.hpp>
#include <fcppt/chrono/steady_clock_fwd.hpp>
#include <fcppt/chrono/system_clock_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace timer
{
namespace clocks
{
template<typename Clock>
struct is_stateful
	: boost::true_type
{};

template<>
struct is_stateful<fcppt::chrono::high_resolution_clock>
	: boost::false_type
{};

template<>
struct is_stateful<fcppt::chrono::steady_clock>
	: boost::false_type
{};

template<>
struct is_stateful<fcppt::chrono::system_clock>
	: boost::false_type
{};

}
}
}

#endif
