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


#ifndef SGE_IMAGE_VIEW_MAKE_MIZUIRO_TYPE_HPP_INCLUDED
#define SGE_IMAGE_VIEW_MAKE_MIZUIRO_TYPE_HPP_INCLUDED

#include <sge/image/view/basic_format.hpp>
#include <sge/image/view/mizuiro_type.hpp>
#include <mizuiro/color/access/heterogenous_raw.hpp>
#include <mizuiro/color/access/homogenous_raw.hpp>
#include <mizuiro/color/types/heterogenous_raw.hpp>
#include <mizuiro/color/types/homogenous_raw.hpp>
#include <mizuiro/image/view_impl.hpp>
#include <mizuiro/image/access/interleaved.hpp>
#include <mizuiro/image/types/interleaved.hpp>
#include <mizuiro/image/types/interleaved_raw.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace image
{
namespace view
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename ColorFormat,
	typename Dim,
	typename Constness
>
struct make_mizuiro_type
:
sge::image::view::mizuiro_type<
	typename sge::image::view::basic_format<
		Dim::value,
		ColorFormat
	>::type,
	Constness
>
{
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
