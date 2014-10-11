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


#ifndef SGE_TIMER_BASIC_DECL_HPP_INCLUDED
#define SGE_TIMER_BASIC_DECL_HPP_INCLUDED

#include <sge/timer/basic_fwd.hpp>
#include <sge/timer/parameters_decl.hpp>
#include <sge/timer/clocks/detail/wrapper.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace timer
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Clock
>
class basic final
:
	sge::timer::clocks::detail::wrapper<
		Clock
	>
{
	FCPPT_NONCOPYABLE(
		basic
	);

	typedef
	sge::timer::clocks::detail::wrapper<
		Clock
	>
	base;
public:
	typedef
	Clock
	clock_type;

	typedef
	sge::timer::parameters<
		clock_type
	>
	parameters;

	typedef typename
	clock_type::time_point
	time_point;

	typedef typename
	clock_type::duration
	duration;

	explicit
	basic(
		parameters const &
	);

	~basic();

	bool
	expired() const;

	void
	expired(
		bool
	);

	bool
	active() const;

	void
	active(
		bool
	);

	template<
		typename NewDuration
	>
	NewDuration const
	interval() const;

	template<
		typename NewDuration
	>
	void
	interval(
		NewDuration const &
	);

	time_point const
	now() const;

	time_point const
	last_time() const;

	void
	reset();
private:
	duration interval_;

	bool active_;

	bool expired_;

	time_point last_time_;
};

FCPPT_PP_POP_WARNING

}
}

#endif
