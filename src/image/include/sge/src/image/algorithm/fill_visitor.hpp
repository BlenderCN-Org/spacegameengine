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


#ifndef SGE_SRC_IMAGE_ALGORITHM_FILL_VISITOR_HPP_INCLUDED
#define SGE_SRC_IMAGE_ALGORITHM_FILL_VISITOR_HPP_INCLUDED

#include <sge/image/mizuiro_color.hpp>
#include <sge/image/color/any/convert.hpp>
#include <mizuiro/color/object_impl.hpp>
#include <mizuiro/image/view_impl.hpp>
#include <mizuiro/image/algorithm/fill_c.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace image
{
namespace algorithm
{

template<
	typename Value
>
class fill_visitor
{
	FCPPT_NONASSIGNABLE(
		fill_visitor
	);
public:
	typedef void result_type;

	explicit
	fill_visitor(
		Value const &_value
	)
	:
		value_(
			_value
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
		mizuiro::image::algorithm::fill_c(
			_view,
			sge::image::color::any::convert<
				typename View::format::color_format
			>(
				value_
			)
		);
	}
private:
	Value const &value_;
};

}
}
}

#endif
