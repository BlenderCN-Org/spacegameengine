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


#ifndef SGE_MATH_VECTOR_CROSS_HPP_INCLUDED
#define SGE_MATH_VECTOR_CROSS_HPP_INCLUDED

#include <sge/math/vector/basic_impl.hpp>

namespace sge
{
namespace math
{
namespace vector
{

template<
	typename T,
	typename N,
	typename S
>
basic<T, N, S> const
cross(
	basic<T, N, S> const &l,
	basic<T, N, S> const &r)
{
	return basic<T, N, S>(
		l.y() * r.z() - l.z() * r.y(),
		l.z() * r.x() - l.x() * r.z(),
		l.x() * r.y() - l.y() * r.x());
}

}
}
}

#endif
