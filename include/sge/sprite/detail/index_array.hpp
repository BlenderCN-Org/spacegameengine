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


#ifndef SGE_SPRITE_DETAIL_INDEX_ARRAY_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_INDEX_ARRAY_HPP_INCLUDED

#include <sge/sprite/detail/constants.hpp>
#include <tr1/array>
#include <boost/cstdint.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

typedef std::tr1::array<
	boost::uint32_t,
	indices_per_sprite
> index_array_type;

extern index_array_type const index_array;

}
}
}

#endif
