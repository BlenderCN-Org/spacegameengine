/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_TRANSFORM_PIXELS_HPP_INCLUDED
#define SGE_RENDERER_TRANSFORM_PIXELS_HPP_INCLUDED

#include "image_view.hpp"
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>
#include <boost/gil/algorithm.hpp>
#include <boost/bind.hpp>

namespace sge
{
namespace renderer
{

template<
	typename Op
>
struct transform_pixels_fn {
	typedef void result_type;

	explicit transform_pixels_fn(
		Op const &op)
	:
		op(op)
	{}

	template<
		typename Src,
		typename Dest
	>
	void operator()(
		Src const &src,
		Dest const &dest) const
	{
		boost::gil::transform_pixels(
			src,
			dest,
			op);
	}
private:
	Op const op;
};

template<
	typename Op
>
void transform_pixels(
	const_image_view const &src,
	image_view const &dst,
	Op const &op)
{
	boost::gil::apply_operation(
		src,
		dst,
		transform_pixels_fn<Op>(
			op));
}

template<
	typename Src,
	typename Op
>
void transform_pixels(
	Src const &src,
	image_view const &dest,
	Op const &op)
{
	boost::gil::apply_operation(
		dest,
		boost::bind(
			transform_pixels_fn<Op>(
				op),
			src,
			_1));
}

template<
	typename Dest,
	typename Op
>
void transform_pixels(
	const_image_view const &src,
	Dest const &dest,
	Op const &op)
{
	boost::gil::apply_operation(
		src,
		boost::bind(
			transform_pixels_fn<Op>(
				op),
			_1,
			dest));
}

}
}

#endif
