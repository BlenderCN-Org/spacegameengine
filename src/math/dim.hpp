/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_MATH_DIM_HPP_INCLUDED
#define SGE_MATH_DIM_HPP_INCLUDED

#include <cstddef>
#include <iterator>
#include <ostream>
#include <cassert>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include "../types.hpp"

#ifndef SGE_MATH_DIM_MAX_SIZE
#define SGE_MATH_DIM_MAX_SIZE 3
#endif

namespace sge
{
namespace math
{

template<typename T, std::size_t Dim>
class dim {
	BOOST_STATIC_ASSERT(Dim > 1 && Dim <= SGE_MATH_DIM_MAX_SIZE);
public:
	typedef T value_type;
	typedef T&             reference;
	typedef const T&       const_reference;
	typedef std::ptrdiff_t difference_type;
	typedef std::size_t    size_type;
	typedef T*             pointer;
	typedef const T*       const_pointer;
	typedef pointer        iterator;
	typedef const_pointer  const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

#define SGE_MATH_DIM_CTOR_ASSIGN_N(z, n, text) (*this)[n] = text##n;
#define SGE_MATH_DIM_CTOR(z, n, text) dim(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_DIM_CTOR_ASSIGN_N, param) }
	BOOST_PP_REPEAT(SGE_MATH_DIM_MAX_SIZE, SGE_MATH_DIM_CTOR, void)

	dim()
	{
		for(size_type i = 0; i < Dim; ++i)
			data[i] = 0;
	}

	reference operator[](const size_type pos)
	{
		assert(pos < Dim);
		return data[pos];
	}

	const_reference operator[](const size_type pos) const
	{
		assert(pos < Dim);
		return data[pos];
	}
	
	bool operator==(const dim& r) const
	{
		for(size_type i = 0; i < Dim; ++i)
			if(data[i] != r[i])
				return false;
		return true;
	}

	bool operator!=(const dim& r) const
	{
		return !((*this)==r);
	}

	dim& operator+=(const dim& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data[i] += r[i];
		return *this;
	}

	dim& operator-=(const dim& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data[i] -= r[i];
		return *this;
	}

	reference w()
	{
		return (*this)[0];
	}

	const_reference w() const
	{
		return (*this)[0];
	}

	reference h()
	{
		return (*this)[1];
	}
	
	const_reference h() const
	{
		return (*this)[1];
	}

	reference d()
	{
		assert(Dim > 2);
		return (*this)[2];
	}
	
	const_reference d() const
	{
		assert(Dim > 2);
		return (*this)[2];
	}

	size_type size() const
	{
		return Dim;
	}

	iterator begin()
	{
		return data;
	}

	iterator end()
	{
		return &data[Dim];
	}

	const_iterator begin() const
	{
		return data;
	}

	const_iterator end() const
	{
		return &data[Dim];
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rbegin() const
	{
		return reverse_iterator(end());
	}

	const_reverse_iterator rend() const
	{
		return reverse_iterator(begin());
	}
private:
	T data[Dim];
};

template<typename T, std::size_t Dim> dim<T,Dim> operator+(const dim<T,Dim>& l, const dim<T,Dim>& r)
{
	return dim<T,Dim>(l) += r;
}


template<typename T, std::size_t Dim> dim<T,Dim> operator-(const dim<T,Dim>& l, const dim<T,Dim>& r)
{
	return dim<T,Dim>(l) -= r;
}

template<typename T, std::size_t Dim>
std::ostream& operator<< (std::ostream& s, const dim<T,Dim>& v)
{
	s << '(';
	for(typename dim<T,Dim>::size_type i = 0; i < Dim-1; ++i)
		s << v[i] << ',';
	s << v[Dim-1] << ')';
	return s;
}

typedef dim<space_unit,2> dim2;
typedef dim<space_unit,3> dim3;

}
}

#endif

