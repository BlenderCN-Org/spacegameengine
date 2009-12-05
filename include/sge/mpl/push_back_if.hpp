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


#ifndef SGE_MPL_PUSH_BACK_IF_HPP_INCLUDED
#define SGE_MPL_PUSH_BACK_IF_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/mpl/push_back.hpp>

namespace sge
{
namespace mpl
{

template<
	typename Condition,
	typename Sequence,
	typename Element
>
struct push_back_if
:
boost::mpl::if_<
	Condition,
	boost::mpl::push_back<
		Sequence,
		Element
	>,
	Sequence
>
{};

}
}

#endif
