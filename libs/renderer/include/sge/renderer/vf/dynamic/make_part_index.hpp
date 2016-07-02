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


#ifndef SGE_RENDERER_VF_DYNAMIC_MAKE_PART_INDEX_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_MAKE_PART_INDEX_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/mpl/index_of.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

template<
	typename Format,
	typename Part
>
sge::renderer::vf::dynamic::part_index
make_part_index()
{
	return
		fcppt::strong_typedef_construct_cast<
			sge::renderer::vf::dynamic::part_index,
			fcppt::cast::static_cast_fun
		>(
			fcppt::mpl::index_of<
				typename Format::parts,
				Part
			>::value
		);
}

}
}
}
}

#endif