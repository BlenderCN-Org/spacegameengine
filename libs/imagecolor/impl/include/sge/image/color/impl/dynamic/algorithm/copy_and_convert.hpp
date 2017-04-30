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


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_COPY_AND_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_COPY_AND_CONVERT_HPP_INCLUDED

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/visitor.hpp>
#include <sge/image/color/impl/dynamic/format/object_decl.hpp>
#include <sge/image/color/impl/dynamic/format/object_traits.hpp>
#include <sge/image/color/impl/dynamic/view/from_static_visitor.hpp>
#include <sge/image/traits/image/dimension.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/object.hpp>
#include <mizuiro/const_tag.hpp>
#include <mizuiro/nonconst_tag.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/variant/apply_unary.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace impl
{
namespace dynamic
{
namespace algorithm
{

template<
	typename Tag
>
void
copy_and_convert(
	sge::image::view::const_object<
		Tag
	> const &_source,
	sge::image::view::object<
		Tag
	> const &_dest,
	sge::image::algorithm::may_overlap const _overlap,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	typedef
	sge::image::traits::image::dimension<
		Tag
	>
	dim;

	fcppt::variant::apply_binary(
		sge::image::color::impl::dynamic::algorithm::cac::visitor(
			_overlap,
			_uninitialized
		),
		fcppt::variant::apply_unary(
			sge::image::color::impl::dynamic::view::from_static_visitor<
				dim::value,
				mizuiro::const_tag
			>(),
			_source.get()
		),
		fcppt::variant::apply_unary(
			sge::image::color::impl::dynamic::view::from_static_visitor<
				dim::value,
				mizuiro::nonconst_tag
			>(),
			_dest.get()
		)
	);
}

}
}
}
}
}
}

#endif
