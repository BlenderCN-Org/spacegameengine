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


#ifndef SGE_RENDERER_VF_DETAIL_READ_WRAPPER_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_READ_WRAPPER_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/detail/read_wrapper_decl.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


template<
	typename T,
	typename Enable
>
inline
sge::renderer::vf::detail::read_wrapper<
	T,
	Enable
>::read_wrapper()
:
	value_(
		fcppt::no_init()
	)
{
}

template<
	typename T,
	typename Enable
>
inline
sge::renderer::vf::detail::read_wrapper<
	T,
	Enable
>::~read_wrapper()
{
}

template<
	typename T,
	typename Enable
>
inline
T &
sge::renderer::vf::detail::read_wrapper<
	T,
	Enable
>::get()
{
	return value_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename T
>
inline
sge::renderer::vf::detail::read_wrapper<
	T,
	std::enable_if_t<
		std::is_fundamental<
			T
		>::value
	>
>::read_wrapper()
// Don't initialize value_
{
}

FCPPT_PP_POP_WARNING

template<
	typename T
>
inline
sge::renderer::vf::detail::read_wrapper<
	T,
	std::enable_if_t<
		std::is_fundamental<
			T
		>::value
	>
>::~read_wrapper()
{
}

template<
	typename T
>
inline
T &
sge::renderer::vf::detail::read_wrapper<
	T,
	std::enable_if_t<
		std::is_fundamental<
			T
		>::value
	>
>::get()
{
	return value_;
}

#endif
