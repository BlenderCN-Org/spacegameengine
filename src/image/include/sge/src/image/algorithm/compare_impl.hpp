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


#ifndef SGE_SRC_IMAGE_ALGORITHM_COMPARE_IMPL_HPP_INCLUDED
#define SGE_SRC_IMAGE_ALGORITHM_COMPARE_IMPL_HPP_INCLUDED

#include <sge/image/algorithm/compare.hpp>
#include <sge/image/traits/const_view_fwd.hpp>
#include <sge/src/image/algorithm/compare_visitor.hpp>
#include <fcppt/variant/apply_binary.hpp>


template<
	typename Tag
>
bool
sge::image::algorithm::compare(
	typename sge::image::traits::const_view<
		Tag
	>::type const &_src1,
	typename sge::image::traits::const_view<
		Tag
	>::type const &_src2
)
{
	return
		fcppt::variant::apply_binary(
			sge::image::algorithm::compare_visitor(),
			_src1.get(),
			_src2.get()
		);
}

#endif
