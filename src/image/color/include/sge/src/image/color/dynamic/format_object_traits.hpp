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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_OBJECT_TRAITS_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_OBJECT_TRAITS_HPP_INCLUDED

#include <sge/src/image/color/dynamic/format_object_fwd.hpp>
#include <mizuiro/color/is_homogenous_dynamic.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace mizuiro
{
namespace color
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename BaseType,
	unsigned NumChannels
>
struct is_homogenous_dynamic<
	sge::image::color::dynamic::format_object<
		BaseType,
		NumChannels
	>
>
:
std::true_type
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
