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


#include <sge/image/impl/view/instantiate_pitch.hpp>
#include <sge/image/impl/view/pitch_impl.hpp>
#include <sge/image3d/pitch.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object.hpp>
#include <sge/image3d/view/pitch.hpp>


sge::image3d::pitch
sge::image3d::view::pitch(
	sge::image3d::view::object const &_view
)
{
	return
		sge::image::view::pitch<
			sge::image3d::tag
		>(
			_view
		);
}

sge::image3d::pitch
sge::image3d::view::pitch(
	sge::image3d::view::const_object const &_view
)
{
	return
		sge::image::view::pitch<
			sge::image3d::tag
		>(
			_view
		);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_PITCH(
	sge::image3d::tag
);
