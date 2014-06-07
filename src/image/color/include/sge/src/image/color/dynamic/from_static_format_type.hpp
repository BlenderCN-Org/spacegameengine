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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_FROM_STATIC_FORMAT_TYPE_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_FROM_STATIC_FORMAT_TYPE_HPP_INCLUDED

#include <sge/src/image/color/dynamic/from_static_format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace dynamic
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Format
>
struct from_static_format_type
:
std::remove_const<
	typename std::remove_reference<
		decltype(
			sge::image::color::dynamic::from_static_format(
				std::declval<
					Format
				>()
			)
		)
	>::type
>
{
};

FCPPT_PP_POP_WARNING

}
}
}
}

#endif
