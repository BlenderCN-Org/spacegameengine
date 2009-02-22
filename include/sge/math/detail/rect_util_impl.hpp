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


#ifndef SGE_MATH_DETAIL_RECT_UTIL_IMPL_HPP_INCLUDED
#define SGE_MATH_DETAIL_RECT_UTIL_IMPL_HPP_INCLUDED

#include <sge/math/vector/basic_impl.hpp>
#include <sge/assert.hpp>
#include <algorithm>

template<
	typename T,
	typename N,
	typename S
>
bool
sge::math::contains(
	rect<T> const &r, 
	vector::basic<T, N, S> const &p)
{
	return p.x() >= r.left() && p.x() <= r.right() &&
	       p.y() >= r.top()  && p.y() <= r.bottom();
}

template<typename T>
bool sge::math::contains(const rect<T>& outer,
                         const rect<T>& inner)
{
	return inner.left() >= outer.left() && inner.right() <= outer.right() &&
	       inner.top() >= outer.top() && inner.bottom() <= outer.bottom();
}

template<typename T>
bool sge::math::intersects(const rect<T>& l, const rect<T>& r)
{
	return !(l.bottom()   < r.top()
	         || l.top()   > r.bottom()
	         || l.right() < r.left()
	         || l.left()  > r.right());
}

template<typename T>
sge::math::rect<T> const sge::math::intersection(rect<T> const &r1,rect<T> const &r2)
{
	if (!intersects(r1,r2))
		return rect<T>(
			static_cast<T>(0),
			static_cast<T>(0),
			static_cast<T>(0),
			static_cast<T>(0));

	return rect<T>(
		std::max(r1.left(),r2.left()), 
		std::max(r1.top(),r2.top()), 
		std::min(r1.right(),r2.right()), 
		std::min(r1.bottom(),r2.bottom()));

}

template<
	typename T,
	typename U
>
sge::math::rect<T> const sge::math::bounding(U it,U const end)
{
	SGE_ASSERT(it != end);

	rect<T> r(*it);

	for (;it != end; ++it)
	{
		r.left() = std::min(it->left(),r.left());
		r.right() = std::max(it->right(),r.right());
		r.top() = std::min(it->top(),r.top());
		r.bottom() = std::max(it->bottom(),r.bottom());
	}
	
	return r;

}

#endif
