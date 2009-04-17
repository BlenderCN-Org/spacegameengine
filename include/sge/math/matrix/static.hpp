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


#ifndef SGE_MATH_MATRIX_STATIC_HPP_INCLUDED
#define SGE_MATH_MATRIX_STATIC_HPP_INCLUDED

#include <sge/math/matrix/basic_fwd.hpp>
#include <sge/math/size_type.hpp>
#include <sge/restrict_typedef_struct.hpp>
#include <boost/mpl/integral_c.hpp>

namespace sge
{
namespace math
{
namespace matrix 
{

template<
	typename T,
	size_type N,
	size_type M
>
class static_ {
public:
	typedef basic<
		T,
		boost::mpl::integral_c<
			size_type,
			N
		>,
		boost::mpl::integral_c<
			size_type,
			M
		>,
		T[N * M]
	> type;

	SGE_RESTRICT_TYPEDEF_STRUCT(static_)
};

}
}
}

#endif
