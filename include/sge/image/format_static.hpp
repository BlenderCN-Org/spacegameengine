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


#ifndef SGE_IMAGE_FORMAT_STATIC_HPP_INCLUDED
#define SGE_IMAGE_FORMAT_STATIC_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/mpl/index_of.hpp>
#include <fcppt/mpl/integral_cast.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/size.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Format,
	typename Elements,
	typename Type
>
struct format_static
:
fcppt::mpl::integral_cast<
	Format,
	fcppt::cast::static_cast_fun,
	fcppt::mpl::index_of<
		Elements,
		Type
	>
>
{
	static_assert(
		fcppt::mpl::integral_cast<
			sge::image::size_type,
			fcppt::cast::static_cast_fun,
			typename
			boost::mpl::size<
				Elements
			>::type
		>::value
		==
		fcppt::cast::size<
			sge::image::size_type
		>(
			fcppt::enum_size<
				Format
			>::value
		),
		"image format mpl::vectors must have the same size as the enum"
	);
};

FCPPT_PP_POP_WARNING

}
}

#endif
