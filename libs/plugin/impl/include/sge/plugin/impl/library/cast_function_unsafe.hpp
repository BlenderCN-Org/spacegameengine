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


#ifndef SGE_PLUGIN_IMPL_LIBRARY_CAST_FUNCTION_UNSAFE_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_LIBRARY_CAST_FUNCTION_UNSAFE_HPP_INCLUDED

#include <sge/plugin/impl/library/is_function_ptr.hpp>
#include <fcppt/config/gcc_version_at_least.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace plugin
{
namespace impl
{
namespace library
{

template<
	typename Target,
	typename Source
>
inline
Target
cast_function_unsafe(
	Source const _function
)
{
	static_assert(
		sge::plugin::impl::library::is_function_ptr<
			Target
		>::value,
		"Target must be a function pointer type"
	);

	static_assert(
		sge::plugin::impl::library::is_function_ptr<
			Source
		>::value,
		"Source must be a function pointer type"
	);

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4191)
#if FCPPT_CONFIG_GCC_VERSION_AT_LEAST(8,0)
FCPPT_PP_DISABLE_GCC_WARNING(-Wcast-function-type)
#endif
	return
		reinterpret_cast<
			Target
		>(
			_function
		);
FCPPT_PP_POP_WARNING
}

}
}
}
}

#endif
