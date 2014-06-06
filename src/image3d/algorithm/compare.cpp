/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image3d/tag.hpp>
#include <sge/image3d/algorithm/compare.hpp>
#include <sge/image3d/traits/const_view_fwd.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/src/image/algorithm/compare_impl.hpp>
#include <sge/src/image/algorithm/instantiate_compare.hpp>


bool
sge::image3d::algorithm::compare(
	sge::image3d::view::const_object const &_src1,
	sge::image3d::view::const_object const &_src2
)
{
	return
		sge::image::algorithm::compare<
			sge::image3d::tag
		>(
			_src1,
			_src2
		);
}

SGE_SRC_IMAGE_ALGORITHM_INSTANTIATE_COMPARE(
	sge::image3d::tag
);
