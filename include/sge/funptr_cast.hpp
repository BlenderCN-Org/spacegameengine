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


#ifndef SGE_FUNPTR_CAST_HPP_INCLUDED
#define SGE_FUNPTR_CAST_HPP_INCLUDED

#include <sge/config.h>
#include <boost/static_assert.hpp>
#include <cstddef>

namespace sge
{

// This function is only intended to make working
// with the broken POSIX interface for getting functions from
// DSOs possible. Do not use this yourself!

template<typename Dest, typename Source>
Dest funptr_cast(const Source& s)
{
	// note: this is UB but sadly it is required for dlsym
	BOOST_STATIC_ASSERT(sizeof(std::size_t) == sizeof(void*));
	typedef std::size_t temp_type;
	return reinterpret_cast<Dest>(reinterpret_cast<temp_type>(s));
}

}

#endif
