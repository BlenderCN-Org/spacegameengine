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


#ifndef SGE_RENDERER_VF_DYNAMIC_MAKE_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_MAKE_FORMAT_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/element_list.hpp>
#include <sge/renderer/vf/dynamic/offset_list.hpp>
#include <sge/renderer/vf/dynamic/detail/make_elements.hpp>
#include <sge/renderer/vf/dynamic/detail/make_offsets.hpp>
#include <sge/renderer/vf/format.hpp>
#include <boost/mpl/for_each.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

template<
	typename Format
>
dynamic::format const
make_format()
{
	typedef typename Format::elements elements;

	typedef typename Format::offsets offsets;

	element_list elems;

	boost::mpl::for_each<
		elements
	>(
		detail::make_elements(
			elems
		)
	);

	offset_list offs;

	boost::mpl::for_each<
		offsets
	>(
		detail::make_offsets(
			offs
		)
	);

	return
		format(
			elems,
			offs
		);
}

}
}
}
}

#endif
