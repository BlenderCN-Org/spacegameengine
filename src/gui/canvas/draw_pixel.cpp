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


#include <sge/gui/canvas/object.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/image2d/rect.hpp>
#include <fcppt/math/box/contains_point.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/lexical_cast.hpp>

void sge::gui::canvas::object::draw_pixel(
	point const &p,
	color const c)
{
	FCPPT_ASSERT_MESSAGE(
		contains_point(area(),p),
		FCPPT_TEXT("tried to draw pixel ")+
		fcppt::lexical_cast<fcppt::string>(p)+
		FCPPT_TEXT(" which is not inside rect ")+
		fcppt::lexical_cast<fcppt::string>(area()));

	sge::image2d::algorithm::fill(
		sge::image2d::view::sub(
			view_,
			fcppt::math::box::structure_cast<
				sge::image2d::rect
			>(
				rect(
					p,
					dim(1,1)
				)
			)
		),
		c
	);
}
