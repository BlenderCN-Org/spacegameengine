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


#ifndef SGE_ALGORITHM_IMPL_HPP_INCLUDED
#define SGE_ALGORITHM_IMPL_HPP_INCLUDED

#include <algorithm>
#include <iterator>

template<typename In, typename Size, typename T>
In sge::find_nth(In first, const In last, const Size count, const T& t)
{
	for(Size c = 0; c < count && first != last; ++c)
		first = std::find(first, last, t);
	return first;
}

template<typename In, typename Size, typename UnaryPredicate>
In sge::find_nth_if(In first, const In last, const Size count, UnaryPredicate pred)
{
	for(Size c = 0; c < count && first != last; ++c)
		first = std::find_if(first, last, pred);
	return first;
}

template<typename In, typename Size, typename BinaryPredicate>
In sge::first_mismatch_if(In first, const In last, Size& cnt, BinaryPredicate pred)
{
	cnt = 0;
	if(first == last)
		return last;

	typename std::iterator_traits<In>::reference ref = *first++;
	cnt = 1;
	for(;first != last; ++first)
	{
		if(!pred(*first,ref))
			return first;
		++cnt;
	}
	return last;
}

template<typename In, typename Out, typename Size>
Out sge::copy_n(const In beg, const Size sz, const Out out)
{
	return std::copy(beg, beg + sz, out);
}

#endif
