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


#ifndef SGE_MATH_VECTOR_HPP_INCLUDED
#define SGE_MATH_VECTOR_HPP_INCLUDED

#include "basic_sequence.hpp"

namespace sge
{
namespace math
{
namespace detail
{

template<
	typename T,
	dim_type Dim>
class vector_policy;

template<
	typename T>
class vector_policy<T, 1> {
protected:
	typedef T &reference;
	typedef T const &const_reference;
	typedef T* pointer;
public:
	reference x();
	const_reference x() const;
protected:
	vector_policy(
		pointer);
	pointer data_;
};

template<
	typename T>
class vector_policy<T, 2> 
	: public vector_policy<T, 1> {
protected:
	typedef vector_policy<T, 1> base;
	typedef typename base::reference reference;
	typedef typename base::const_reference const_reference;
	typedef typename base::pointer pointer;
public:
	reference y();
	const_reference y() const;
protected:
	vector_policy(
		pointer);
};

template<
	typename T>
class vector_policy<T, 3> 
	: public vector_policy<T, 2> {
protected:
	typedef vector_policy<T, 2> base;
	typedef typename base::reference reference;
	typedef typename base::const_reference const_reference;
	typedef typename base::pointer pointer;
public:
	reference z();
	const_reference z() const;
protected:
	vector_policy(
		pointer);
};

template<
	typename T,
	dim_type Dim>
class vector_policy
	: public vector_policy<T, 3> {
	typedef vector_policy<T, 3> base;
	typedef typename base::reference reference;
	typedef typename base::const_reference const_reference;
	typedef typename base::pointer pointer;
public:
	reference x();
	const_reference x() const;
	reference y();
	const_reference y() const;
	reference z();
	const_reference z() const;
protected:
	vector_policy(
		pointer);
private:
	pointer data_;	
};

}

}
}
//#endif

#define basic_vector_ext(T, Dim) sge::math::basic_sequence<T, Dim, sge::math::detail::vector_policy>

#include "../config.h"
#include "compare.hpp"
#include "mod.hpp"
#include "../exception.hpp"
#include "../text.hpp"
#include "../su.hpp"
#include "../no_initialization_tag.hpp"
#include "../exception.hpp"
#ifndef SGE_HAVE_VARIADIC_TEMPLATES
#include <boost/static_assert.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#endif
#include <boost/utility/enable_if.hpp>
#include <iterator>
#include <istream>
#include <ostream>
#include <cassert>
#include <cstddef>
#include <cmath>

#ifndef SGE_HAVE_VARIADIC_TEMPLATES
#ifndef SGE_MATH_VECTOR_MAX_SIZE
#define SGE_MATH_VECTOR_MAX_SIZE 4
#endif
#endif

namespace sge
{
namespace math
{

/** 
 * This class should be used for representing vectors, so either points or
 * direction vectors. You could also store size values in here, but there are
 * no accessors like "w" or "h". Use sge::math::basic_rect or
 * sge::math::basic_dim for that purpose.
 *
 * basic_vector uses C++0x variadic templates where available.
 */
template<typename T, std::size_t Dim>
class basic_vector {
#ifndef SGE_HAVE_VARIADIC_TEMPLATES
	BOOST_STATIC_ASSERT(Dim <= SGE_MATH_VECTOR_MAX_SIZE);
#endif
public:
	typedef T              value_type;
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

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
	template<typename... Args>
	explicit basic_vector(Args... args)
	{
#ifdef SGE_HAVE_STATIC_ASSERT
		static_assert(sizeof...(args) == Dim, "Invalid number of arguments to math::vector ctor!");
#else
		BOOST_STATIC_ASSERT(sizeof...(args) == Dim);
#endif
		set(args...);
	}
#else
#define SGE_MATH_VECTOR_CTOR_ASSIGN_N(z, n, text) (*this)[n] = text##n;
#define SGE_MATH_VECTOR_CTOR(z, n, text) basic_vector(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_VECTOR_CTOR_ASSIGN_N, param) }
	BOOST_PP_REPEAT(SGE_MATH_VECTOR_MAX_SIZE, SGE_MATH_VECTOR_CTOR, void)
#endif

	/**
	 * This initializes the vector with zero
	 */
	basic_vector()
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] = static_cast<T>(0);
	}

	/**
	 * This does not initialize any of the coordinates (models the built types)
	 */
	basic_vector(no_initialization_tag)
	{
	}

	/**
	 * This constructor gets a vector of the same type, but with a dimension
	 * lower. This is just a convenience so you can construct, for example, a
	 * vector3 from a vector2 by writing \code basic_vector<T,2> small;
	 * basic_vector<T,3> large(small,0); \endcode
	 */
	template<std::size_t U>
	basic_vector(const basic_vector<T,U>& v, typename boost::enable_if_c<U == Dim - 1, const_reference>::type n = 0)
	{
		for(size_type i = 0; i < U; ++i)
			data_[i] = v[i];
		data_[U] = n;
	}

	basic_vector(const basic_vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] = r[i];
	}

	basic_vector& operator=(const basic_vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] = r[i];
		return *this;
	}

	basic_vector& operator+=(const basic_vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] += r[i];
		return *this;
	}

	basic_vector& operator-=(const basic_vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] -= r[i];
		return *this;
	}

	basic_vector operator+(const basic_vector& r) const
	{
		return basic_vector(*this) += r;
	}

	basic_vector operator-(const basic_vector& r) const
	{
		return basic_vector(*this) -= r;
	}

	basic_vector operator+() const
	{
		basic_vector ret = basic_vector(no_initialization_tag());
		for(size_type i = 0; i < Dim; ++i)
			ret[i] = +data_[i];
		return ret;
	}

	basic_vector operator-() const
	{
		basic_vector ret = basic_vector(no_initialization_tag());
		for(size_type i = 0; i < Dim; ++i)
			ret[i] = -data_[i];
		return ret;
	}

	/**
	 * Scalar multiplication
	 */
	basic_vector& operator*=(const_reference r)
	{
		for(size_type i = 0; i < Dim; ++i)
			(*this)[i] *= r;
		return *this;
	}

	/**
	 * This does not take the dot or cross product but rather multiplies componentwise
	 */
	basic_vector& operator*=(const basic_vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			(*this)[i] *= r[i];
		return *this;
	}

	/**
	 * Scalar multiplication
	 */
	basic_vector operator*(const_reference r) const
	{
		return basic_vector(*this) *= r;
	}

	/**
	 * This does not take the dot or cross product but rather multiplies componentwise
	 */
	basic_vector operator*(const basic_vector& r) const
	{
		return basic_vector(*this) *= r;
	}

	/**
	 * Scalar multiplication
	 */
	friend basic_vector operator*(const_reference l, basic_vector r)
	{
		return r *= l;
	}

	basic_vector& operator/=(const_reference r)
	{
		for(size_type i = 0; i < Dim; ++i)
			(*this)[i] /= r;
		return *this;
	}

	basic_vector& operator/=(const basic_vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			(*this)[i] /= r[i];
		return *this;
	}

	basic_vector operator/(const_reference r) const
	{
		return basic_vector(*this) /= r;
	}

	basic_vector operator/(const basic_vector& r) const
	{
		return basic_vector(*this) /= r;
	}

	/**
	 * This operator uses sge::math::mod to calculate the modulo
	 */
	basic_vector& operator%=(const_reference r)
	{
		for(size_type i = 0; i < Dim; ++i)
			mod_assign((*this)[i], r);
		return *this;
	}

	/**
	 * This operator uses sge::math::mod to calculate the modulo
	 */
	basic_vector& operator%=(const basic_vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			mod_assign((*this)[i], r[i]);
		return *this;
	}

	/**
	 * This operator uses sge::math::mod to calculate the modulo
	 */
	basic_vector operator%(const_reference r) const
	{
		return basic_vector(*this) %= r;
	}

	/**
	 * This operator uses sge::math::mod to calculate the modulo
	 */
	basic_vector operator%(const basic_vector& r) const
	{
		return basic_vector(*this) %= r;
	}

	value_type dot(const basic_vector& r) const
	{
		value_type ret(0);
		for(size_type i = 0; i < Dim; ++i)
			ret += (*this)[i] * r[i];
		return ret;
	}

	/**
	 * Does range checking with an assertion
	 */
	reference operator[](const size_type pos)
	{
		assert(pos < Dim);
		return data_[pos];
	}

	/**
	 * Does range checking with an assertion
	 */
	const_reference operator[](const size_type pos) const
	{
		assert(pos < Dim);
		return data_[pos];
	}

	/**
	 * \throw sge::exception If argument greater than dimension
	 */
	reference at(const size_type pos)
	{
		if(pos >= Dim)
			throw exception(SGE_TEXT("basic_vector<T, N>::at(): out of range!"));
		return data_[pos];
	}

	/**
	 * \throw sge::exception If argument greater than dimension
	 */
	const_reference at(const size_type pos) const
	{
		if(pos >= Dim)
			throw exception(SGE_TEXT("basic_vector<T, N>::at(): out of range!"));
		return data_[pos];
	}

	/**
	 * Uses sge::math::compare to compare componentwise
	 */
	bool operator==(const basic_vector& r) const
	{
		for(size_type i = 0; i < Dim; ++i)
			if(!compare(data_[i], r[i]))
				return false;
		return true;
	}

	/**
	 * Uses sge::math::compare to compare componentwise
	 */
	bool operator!=(const basic_vector& r) const
	{
		return !((*this)==r);
	}

	/**
	 * Returns the dot product of the vector with itself
	 */
	value_type length_quad() const
	{
		return dot(*this);
	}

	/**
	 * Applies std::sqrt to length_quad.
	 */
	value_type length() const
	{
		return static_cast<value_type>(std::sqrt(length_quad()));
	}

	/**
	 * Returns the normalized vector
	 */
	basic_vector unit() const
	{
		return (*this) * (static_cast<T>(1) / length());
	}

	basic_vector& normalize()
	{
		return *this = unit();
	}

	reference x()
	{
		return (*this)[0];
	}

	const_reference x() const
	{
		return (*this)[0];
	}

	reference y()
	{
		return (*this)[1];
	}

	const_reference y() const
	{
		return (*this)[1];
	}

//	template<typename Dummy>
	reference z(/*typename boost::enable_if_c<(Dim > 2), Dummy>* = 0*/)
	{
		assert(Dim > 2);
		return (*this)[2];
	}

//	template<typename Dummy>
	const_reference z(/*typename boost::enable_if_c<(Dim > 2), Dummy>* = 0*/) const
	{
		assert(Dim > 2);
		return (*this)[2];
	}

	reference w()
	{
		assert(Dim > 3);
		return (*this)[3];
	}

	const_reference w() const
	{
		assert(Dim > 3);
		return (*this)[3];
	}

	//template<typename OtherT>
	//basic_vector cross(const basic_vector& r, typename boost::enable_if<boost::mpl::and_<boost::is_same<T,OtherT>, boost::mpl::bool_<Dim == 3> > >::type* = 0) const
	basic_vector cross(const basic_vector& r) const
	{
		return basic_vector(y()*r.z() - z()*r.y(),
		              z()*r.x() - x()*r.z(),
		              x()*r.y() - y()*r.x());
	}

	/** 
	 * Compares the vector against the default constructed (and thus "nullified")
	 * vector
	 */
	bool is_null() const
	{
		return *this == basic_vector();
	}

	void swap(basic_vector& r)
	{
		std::swap(*this,r);
	}

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
	template<typename... Args>
	void set(const_reference arg, Args... args)
	{
#ifdef SGE_HAVE_STATIC_ASSERT
		static_assert(sizeof...(args) == Dim-1, "Invalid number of arguments to math::vector::set!");
#else
		BOOST_STATIC_ASSERT(sizeof...(args) == Dim);
#endif
		set_impl(0, arg, args...);
	}
private:
	template<typename... Args>
	void set_impl(const size_type i, const_reference arg, Args... args)
	{
		(*this)[i] = arg;
		set_impl(i+1, args...);
	}

	void set_impl(const size_type i, const_reference arg)
	{
		(*this)[i] = arg;
	}
public:
#else
#define SGE_MATH_VECTOR_SET(z, n, text) void set(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_VECTOR_CTOR_ASSIGN_N, param) }
BOOST_PP_REPEAT(SGE_MATH_VECTOR_MAX_SIZE, SGE_MATH_VECTOR_SET, void)
#endif

	bool nearly_equals(const basic_vector& r, const value_type& radius) const
	{
		const basic_vector tmp(*this - r);
		return dot(tmp,tmp) < radius * radius;
	}

	size_type size() const
	{
		return Dim;
	}

	size_type dim() const
	{
		return Dim;
	}

	iterator begin()
	{
		return data_;
	}

	iterator end()
	{
		return &data_[Dim];
	}

	const_iterator begin() const
	{
		return data_;
	}

	const_iterator end() const
	{
		return &data_[Dim];
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

	pointer data()
	{
		return data_;
	}

	const_pointer data() const
	{
		return data_;
	}
private:
	T data_[Dim];
};

template<typename T, std::size_t Dim>
void place(basic_vector<T,Dim>& v,
           const typename basic_vector<T,Dim>::const_reference radius,
           const typename basic_vector<T,Dim>::const_reference high_angle,
           const typename basic_vector<T,Dim>::const_reference plane_angle,
           typename boost::enable_if_c<Dim==3,T>::type* = 0)
{
	v.x() = radius * std::sin(high_angle) * std::cos(plane_angle);
	v.z() = radius * std::sin(high_angle) * std::sin(plane_angle);
	v.y() = radius * std::cos(high_angle);
}

template<typename T, std::size_t Dim>
void swap(basic_vector<T,Dim>& a, basic_vector<T,Dim>& b)
{
	a.swap(b);
}

template<typename T, std::size_t Dim>
basic_vector<T,Dim> cross(const basic_vector<T,Dim>& l, const basic_vector<T,Dim>& r)
{
	return l.cross(r);
}

template<typename T, std::size_t Dim>
basic_vector<T,Dim> normalize(basic_vector<T,Dim> l)
{
	return l.normalize();
}

template<typename T, std::size_t Dim>
typename basic_vector<T,Dim>::value_type dot(const basic_vector<T,Dim>& l, const basic_vector<T,Dim>& r)
{
	return l.dot(r);
}

/**
 * Outputs the vector in the format \f$(v_0,\ldots,v_n)\f$.
 */
template<typename T, std::size_t Dim,typename Ch, typename Traits>
inline std::basic_ostream<Ch,Traits>& operator<< (std::basic_ostream<Ch,Traits>& s, const basic_vector<T,Dim>& v)
{
	s << s.widen('(');
	for(typename basic_vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
		s << v[i] << s.widen(',');
	return s << v[Dim-1] << s.widen(')');
}

/**
 * Reads the vector from the stream in the format \f$(v_0,\ldots,v_n)\f$.
 */
template<typename T, std::size_t Dim,typename Ch, typename Traits>
std::basic_istream<Ch,Traits>& operator>> (std::basic_istream<Ch,Traits>& s, basic_vector<T,Dim>& v)
{
	Ch c;
	s >> c;
	if(c != s.widen('('))
		s.setstate(std::ios_base::failbit);
	for(typename basic_vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
	{
		s >> v[i] >> c;
		if(c != s.widen(','))
			s.setstate(std::ios_base::failbit);
	}
	s >> v[Dim-1] >> c;
	if(c != s.widen(')'))
		s.setstate(std::ios_base::failbit);
	return s;
}

/**
 * Casts the basic_vector<T> to basic_vector<D> (using static_cast).
 */
template<typename D, typename S, std::size_t Dim>
basic_vector<D, Dim> structure_cast(const basic_vector<S, Dim>& s)
{
	typedef basic_vector<D, Dim> ret_type;
	ret_type ret = ret_type(no_initialization_tag());
	for(typename ret_type::size_type i = 0; i < Dim; ++i)
		ret[i] = static_cast<D>(s[i]);
	return ret;

}

typedef basic_vector<space_unit,2> vector2;
typedef basic_vector<space_unit,3> vector3;
typedef basic_vector<space_unit,4> vector4;

}
}

#endif
