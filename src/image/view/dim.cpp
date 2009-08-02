/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/view/dim.hpp>
#include <sge/image/size_type.hpp>
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

namespace
{

template<
	typename GilDim
>
sge::image::dim_type const
gil_dim_to_sge(
	GilDim const &);

class visitor {
public:
	typedef sge::image::dim_type result_type;

	template<
		typename View
	>
	result_type const
	operator()(
		View const &) const;
};

}

sge::image::dim_type const
sge::image::view::dim(
	const_object const &v)
{
	return variant::apply_unary(
		visitor(),
		v
	);
}

namespace
{

template<
	typename Dim 
>
sge::image::dim_type const
gil_dim_to_sge(
	Dim const &v)
{
	// TODO: make this more generic!
	return sge::image::dim_type(
		v[0],
		v[1]
	);
}


template<
	typename View
>
visitor::result_type const
visitor::operator()(
	View const &view) const
{
	return gil_dim_to_sge(
		view.dim()
	);
}

}
