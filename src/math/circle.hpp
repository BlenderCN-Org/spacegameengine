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


#ifndef SGE_CIRCLE_HPP_INCLUDED
#define SGE_CIRCLE_HPP_INCLUDED

#include "../types.hpp"
#include "vector.hpp"

namespace sge
{
namespace math
{

template<typename T> class basic_circle {
public:
	typedef T                                 value_type;
	typedef T&                                reference;
	typedef const T&                          const_reference;
	typedef math::basic_vector<value_type, 2> point_type;

	basic_circle(
		const_reference x,
		const_reference y,
		const_reference radius);

	basic_circle(
		const point_type& origin,
		const_reference radius);

	point_type& origin();
	const point_type& origin() const;
	reference radius();
	const_reference radius() const;
private:
	point_type origin_;
	space_unit radius_;
};

typedef basic_circle<space_unit> circle;

}
}

#endif
