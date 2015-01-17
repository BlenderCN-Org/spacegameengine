/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/traits/color_tag.hpp>
#include <sge/image2d/traits/const_view_fwd.hpp>
#include <sge/image2d/traits/dim_fwd.hpp>
#include <sge/image2d/traits/view_fwd.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/src/image/algorithm/copy_and_convert_impl.hpp>
#include <sge/src/image/algorithm/instantiate_copy_and_convert.hpp>
#include <sge/src/image/color/traits/dynamic_copy_and_convert.hpp>
#include <sge/src/image/color/traits/static_converter.hpp>


void
sge::image2d::algorithm::copy_and_convert(
	sge::image2d::view::const_object const &_src,
	sge::image2d::view::object const &_dest,
	sge::image::algorithm::may_overlap const _overlap
)
{
	sge::image::algorithm::copy_and_convert<
		sge::image2d::tag
	>(
		_src,
		_dest,
		_overlap
	);
}

SGE_SRC_IMAGE_ALGORITHM_INSTANTIATE_COPY_AND_CONVERT(
	sge::image2d::tag
);
