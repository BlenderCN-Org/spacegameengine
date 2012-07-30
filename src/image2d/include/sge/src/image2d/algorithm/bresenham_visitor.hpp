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


#ifndef SGE_SRC_IMAGE2D_ALGORITHM_BRESENHAM_VISITOR_HPP_INCLUDED
#define SGE_SRC_IMAGE2D_ALGORITHM_BRESENHAM_VISITOR_HPP_INCLUDED

#include <sge/image/color/object.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/image2d/vector.hpp>
#include <sge/src/image/convert_dim.hpp>
#include <mizuiro/image/view_impl.hpp>
#include <mizuiro/image/algorithm/bresenham.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace image2d
{
namespace algorithm
{

class bresenham_visitor
{
	FCPPT_NONASSIGNABLE(
		bresenham_visitor
	);
public:
	typedef void result_type;

	bresenham_visitor(
		sge::image2d::vector const &_pos1,
		sge::image2d::vector const &_pos2,
		sge::image::color::any::object const &_color
	)
	:
		pos1_(
			_pos1
		),
		pos2_(
			_pos2
		),
		color_(
			_color
		)
	{
	}

	template<
		typename View
	>
	result_type
	operator()(
		View const &_view
	) const
	{
		mizuiro::image::algorithm::bresenham(
			_view,
			sge::image::convert_dim<
				typename View::dim
			>(
				pos1_
			),
			sge::image::convert_dim<
				typename View::dim
			>(
				pos2_
			),
			sge::image::color::any::convert<
				typename View::format::color_format
			>(
				color_
			)
		);
	}
private:
	sge::image2d::vector const pos1_;

	sge::image2d::vector const pos2_;

	sge::image::color::any::object const &color_;
};

}
}
}

#endif
