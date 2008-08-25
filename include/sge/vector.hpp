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


#ifndef SGE_VECTOR_HPP_INCLUDED
#define SGE_VECTOR_HPP_INCLUDED

#include <vector>

namespace sge
{

template<typename T, typename A>
inline typename std::vector<T,A>::pointer
data(
	std::vector<T,A> &v)
{
	return v.empty() ? 0 : &v[0];
}

template<typename T, typename A>
inline typename std::vector<T,A>::const_pointer
data(
	std::vector<T,A> const &v)
{
	return v.empty() ? 0 : &v[0];
}

template<typename T, typename A>
inline typename std::vector<T,A>::pointer
data_end(
	std::vector<T,A> &v)
{
	return data(v) ? data(v) : data(v) + v.size();
}

template<typename T, typename A>
inline typename std::vector<T,A>::const_pointer
data_end(
	std::vector<T,A> const &v)
{
	return data(v) ? data(v) : data(v) + v.size();
}

}

#endif
