/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VF_UNSPECIFIED_HPP_INCLUDED
#define SGE_RENDERER_VF_UNSPECIFIED_HPP_INCLUDED

#include <sge/renderer/vf/unspecified_base.hpp>
#include <sge/renderer/vf/single_base.hpp>
#include <sge/renderer/vf/vector_base.hpp>
#include <sge/renderer/vf/color_base.hpp>
#include <sge/renderer/vf/vector_fwd.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <mizuiro/color/homogenous_fwd.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/static_assert.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Format,
	typename Tag
>
struct unspecified;

template<
	typename Format,
	typename Tag
>
struct unspecified
:
unspecified_base<
	single_base<
		Format
	>,
	Tag
>
{
	BOOST_STATIC_ASSERT(
		boost::is_fundamental<
			Format
		>::value
	);
};

template<
	typename Format,
	vertex_size NumSubElements,
	typename Tag
>
struct unspecified<
	vector<
		Format,
		NumSubElements
	>,
	Tag
>
:
unspecified_base<
	vector_base<
		Format,
		NumSubElements
	>,
	Tag
>
{
	BOOST_STATIC_ASSERT(
		NumSubElements >= 2
		&& NumSubElements <= 4
	);
};

template<
	typename ColorChannel,
	typename ColorLayout,
	typename Tag
>
struct unspecified<
	mizuiro::color::homogenous<
		ColorChannel,
		ColorLayout
	>,
	Tag
>
:
unspecified_base<
	color_base<
		mizuiro::color::homogenous<
			ColorChannel,
			ColorLayout
		>
	>,
	Tag
>
{};

}
}
}

#endif
