#ifndef SGE_RECT_HPP_INCLUDED
#define SGE_RECT_HPP_INCLUDED

#include "./vector2.hpp"
#include "./line_seg2.hpp"

namespace sge
{
	template<typename T> struct basic_rect {
		typedef T value_type;
		basic_rect(const value_type& left  = value_type(), const value_type& top    = value_type(),
		           const value_type& right = value_type(), const value_type& bottom = value_type())
			: left(left), top(top), right(right), bottom(bottom) {}
			value_type left, top, right, bottom;
	};

	template<typename T> inline bool operator==(const basic_rect<T>& l, const basic_rect<T>& r)
	{
		return l.left == r.left && l.top == r.top && l.right == r.right && l.bottom == r.bottom;
	}

	template<typename T> inline bool operator!=(const basic_rect<T>& l, const basic_rect<T>& r)
	{
		return !(l==r);
	}

	template<typename T> inline bool intersects(const basic_rect<T>& r, const vector2<T>& p)
	{
		return p.x >= r.left && p.x <= r.right &&
		       p.y >= r.top  && p.y <= r.bottom;
	}

	template<typename T> inline bool intersects(const basic_rect<T>& l, const basic_rect<T>& r)
	{
		return ((l.left <= r.left && r.left <= l.right) ||
		       (l.left <= r.right && r.right <= l.right)) &&
		       ((l.top <= r.top && r.top <= l.bottom) ||
		       (l.top <= r.bottom && r.bottom <= l.bottom));
	}

	template<typename T> inline bool intersects(const basic_rect<T>& r, const line_seg2<T>& l)
	{
		typedef typename line_seg2<T>::vec vec;
		return intersects(line_seg2<T>(vec(r.left,r.top),vec(r.left,r.bottom)),l) ||
		       intersects(line_seg2<T>(vec(r.left,r.bottom),vec(r.right,r.bottom)),l) ||
		       intersects(line_seg2<T>(vec(r.right,r.bottom),vec(r.right,r.top)),l) ||
		       intersects(line_seg2<T>(vec(r.right,r.top),vec(r.left,r.top)),l);
	}

	template<typename T> inline basic_rect<T> operator+(const basic_rect<T>& l, const vector2<T>& r)
	{
		return basic_rect<T>(l.left + r.x, l.top + r.y, l.right + r.x, l.bottom + r.y);
	}

	template<typename T, typename Ch, typename Traits> std::basic_ostream<Ch,Traits>& operator<<(std::basic_ostream<Ch,Traits>& s, const basic_rect<T>& r)
	{
		return s << "((" << r.left << ',' << r.top << "),(" << r.right << ',' << r.bottom << "))";
	}
}

#endif
