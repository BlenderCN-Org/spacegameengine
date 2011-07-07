/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_IMAGE_ALGORITHM_COPY_AND_CONVERT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_ALGORITHM_COPY_AND_CONVERT_IMPL_HPP_INCLUDED

#define SGE_IMAGE_INSTANTIATE_EXPORTS
#include <sge/image/algorithm/copy_and_convert.hpp>
#undef SGE_IMAGE_INSTANTIATE_EXPORTS
#include "copy_and_convert_visitor.hpp"
#include <sge/image/traits/const_view.hpp>
#include <sge/image/traits/view.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/variant/object_impl.hpp>

#include "../dynamic/algorithm/copy_and_convert.hpp"

template<
	typename Tag
>
void
sge::image::algorithm::copy_and_convert(
	typename image::traits::const_view<
		Tag
	>::type const &_src,
	typename image::traits::view<
		Tag
	>::type const &_dest
)
{
#if 0
	fcppt::variant::apply_binary(
		algorithm::copy_and_convert_visitor(),
		_src.get(),
		_dest.get()
	);
#endif
	image::dynamic::algorithm::copy_and_convert<
		Tag
	>(
		_src,
		_dest
	);
}

#endif
