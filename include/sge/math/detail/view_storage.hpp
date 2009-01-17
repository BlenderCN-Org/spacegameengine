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


#ifndef SGE_MATH_DETAIL_VIEW_STORAGE_HPP_INCLUDED
#define SGE_MATH_DETAIL_VIEW_STORAGE_HPP_INCLUDED

namespace sge
{
namespace math
{
namespace detail
{

template<
	typename T
	typename N
>
class view_storage {
public:
	typedef typename N::value_type size_type;
	typedef T &reference;
	typedef T *pointer;

	view_storage(
		pointer,
		size_type);

	reference
	operator[](
		size_type);
	
	size_type size() const;
private:
	pointer rep;
	size_type sz;
};

}
}
}

#endif
