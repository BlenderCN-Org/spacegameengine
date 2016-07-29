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


#ifndef SGE_CEGUI_IMPL_FROM_CEGUI_VECTOR3_HPP_INCLUDED
#define SGE_CEGUI_IMPL_FROM_CEGUI_VECTOR3_HPP_INCLUDED

#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Vector.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cegui
{
namespace impl
{

template<
	typename ValueType
>
fcppt::math::vector::static_<
	ValueType,
	3u
>
from_cegui_vector3(
	CEGUI::Vector3<
		ValueType
	> const &_size
)
{
	return
		fcppt::math::vector::static_<
			ValueType,
			3u
		>{
			_size.d_x,
			_size.d_y,
			_size.d_z
		};
}

}
}
}

#endif
