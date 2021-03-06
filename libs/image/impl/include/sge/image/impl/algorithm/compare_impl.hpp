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


#ifndef SGE_IMAGE_IMPL_ALGORITHM_COMPARE_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_COMPARE_IMPL_HPP_INCLUDED

#include <sge/image/algorithm/compare.hpp>
#include <sge/image/impl/algorithm/compare_visitor.hpp>
#include <sge/image/view/const_object.hpp>
#include <fcppt/variant/apply.hpp>


template<
	typename Tag
>
bool
sge::image::algorithm::compare(
	sge::image::view::const_object<
		Tag
	> const &_src1,
	sge::image::view::const_object<
		Tag
	> const &_src2
)
{
	return
		fcppt::variant::apply(
			sge::image::impl::algorithm::compare_visitor(),
			_src1.get(),
			_src2.get()
		);
}

#endif
