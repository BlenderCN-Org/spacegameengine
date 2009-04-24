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



#ifndef SGE_MATH_MATRIX_DETAIL_TRANSPOSE_IMPL_HPP_INCLUDED
#define SGE_MATH_MATRIX_DETAIL_TRANSPOSE_IMPL_HPP_INCLUDED

#include <sge/math/matrix/basic_impl.hpp>

template<
	typename T,
	typename N,
	typename S
>
sge::math::matrix::basic<T, N, N, S> const
sge::math::matrix::transpose(
	basic<T, N, N, S> const &t)
{
	// FIXME!
	basic<T, N, N, S> ret;

	typedef typename basic<T, N, N, S>::size_type size_type;
	for(size_type i = 0; i < t.rows(); ++i)
		for(size_type j = 0; j < t.columns(); ++j)
			if(j < t.rows() && i < t.columns())
				ret[j][i] = t[i][j];
	return ret;
}

#endif
