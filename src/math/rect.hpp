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


#ifndef SGE_RECT_HPP_INCLUDED
#define SGE_RECT_HPP_INCLUDED

#include "../exception.hpp"
#include "line_seg2.hpp"
#include "dim.hpp"
#include "vector.hpp"

namespace sge
{
namespace math 
{
template<typename T> struct basic_rect {
	typedef T value_type;
	typedef math::basic_vector<T,2> point_type;
	typedef math::basic_dim<T,2> dim_type;

	basic_rect(const value_type& left  = value_type(), const value_type& top    = value_type(),
	           const value_type& right = value_type(), const value_type& bottom = value_type())
		: left(left), top(top), right(right), bottom(bottom)
	{}

	basic_rect(const point_type& pos, const dim_type& sz)
		: left(pos.x()), top(pos.y()), right(pos.x() + sz.w()), bottom(pos.y() + sz.h())
	{}

	value_type width() const { return right - left; }
	value_type height() const { return bottom - top; }

	point_type pos() const
	{
		return point_type(left, top);
	}

	dim_type size() const
	{
		return dim_type(width(),height());
	}

	value_type left, top, right, bottom;
};

template<typename T> inline basic_rect<T> operator+(const basic_rect<T>& l, const math::basic_vector<T,2>& r)
{
	return basic_rect<T>(l.left + r.x(), l.top + r.y(), l.right + r.x(), l.bottom + r.y());
}

template<typename T> inline basic_rect<T> operator-(const basic_rect<T>& l, const math::basic_vector<T,2>& r)
{
	return basic_rect<T>(l.left - r.x(), l.top - r.y(), l.right - r.x(), l.bottom - r.y());
}

template<typename T> inline T width(const basic_rect<T>& r)
{
	return r.width();
}

template<typename T> inline T height(const basic_rect<T>& r)
{
	return r.height();
}

template<typename T> inline bool operator==(const basic_rect<T>& l, const basic_rect<T>& r)
{
	return l.left == r.left && l.top == r.top && l.right == r.right && l.bottom == r.bottom;
}

template<typename T> inline bool operator!=(const basic_rect<T>& l, const basic_rect<T>& r)
{
	return !(l==r);
}

template<typename T> inline bool intersects(const basic_rect<T>& r, const math::basic_vector<T,2>& p)
{
	return p.x() >= r.left && p.x() <= r.right &&
	       p.y() >= r.top  && p.y() <= r.bottom;
}

template<typename T> inline bool contains(const basic_rect<T>& outer, const basic_rect<T>& inner)
{
	return inner.left >= outer.left && inner.right <= outer.right &&
	       inner.top >= outer.top && inner.bottom <= outer.bottom;
}

template<typename T> inline bool intersects(const basic_rect<T>& l, const basic_rect<T>& r)
{
	return !(l.bottom < r.top || l.top > r.bottom || l.right < r.left || l.left > r.right);
}

template<typename T> inline bool intersects(const basic_rect<T>& r, const basic_line_seg2<T>& l)
{
	typedef typename basic_line_seg2<T>::vec vec;
	return intersects(basic_line_seg2<T>(vec(r.left, r.top),     vec(r.left,  r.bottom)), l) ||
	       intersects(basic_line_seg2<T>(vec(r.left, r.bottom),  vec(r.right, r.bottom)), l) ||
	       intersects(basic_line_seg2<T>(vec(r.right, r.bottom), vec(r.right, r.top)),    l) ||
	       intersects(basic_line_seg2<T>(vec(r.right, r.top),    vec(r.left,  r.top)),    l);
}

template<typename T, typename Ch, typename Traits>
inline std::basic_ostream<Ch,Traits>& operator<<(std::basic_ostream<Ch,Traits>& s, const basic_rect<T>& r)
{
	return s << s.widen('(') << s.widen('(') << r.left << s.widen(',') << r.top << s.widen(')') << s.widen(',')
	         << s.widen('(') << r.right << s.widen(',') << r.bottom << s.widen(')') << s.widen(')');
}

typedef basic_rect<space_unit> rect;

}
}

#endif
