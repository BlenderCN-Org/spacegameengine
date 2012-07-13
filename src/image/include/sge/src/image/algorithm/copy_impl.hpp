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


#ifndef SGE_SRC_IMAGE_ALGORITHM_COPY_IMPL_HPP_INCLUDED
#define SGE_SRC_IMAGE_ALGORITHM_COPY_IMPL_HPP_INCLUDED

#include <sge/image/algorithm/copy.hpp>
#include <sge/image/algorithm/invalid_copy.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/traits/const_view.hpp>
#include <sge/image/traits/view.hpp>
#include <sge/image/view/format.hpp>
#include <sge/src/image/algorithm/copy_visitor.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/variant/invalid_get.hpp>
#include <fcppt/variant/object_impl.hpp>


template<
	typename Tag
>
void
sge::image::algorithm::copy(
	typename sge::image::traits::const_view<
		Tag
	>::type const &_src,
	typename sge::image::traits::view<
		Tag
	>::type const &_dest,
	sge::image::algorithm::may_overlap::type const _overlap
)
try
{
	fcppt::variant::apply_unary(
		sge::image::algorithm::copy_visitor<
			Tag
		>(
			_dest,
			_overlap
		),
		_src.get()
	);
}
catch(
	fcppt::variant::invalid_get const &
)
{
	throw sge::image::algorithm::invalid_copy(
		sge::image::view::format<
			Tag
		>(
			_src
		),
		sge::image::view::format<
			Tag
		>(
			_dest
		)
	);
}

#endif
