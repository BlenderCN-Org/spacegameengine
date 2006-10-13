/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_TYPES_HPP_INCLUDED
#define SGE_TYPES_HPP_INCLUDED

#ifdef _WIN32
	#define SGE_WINDOWS_PLATFORM 1
#elif __linux__
	#define SGE_LINUX_PLATFORM 1
#endif

namespace sge
{

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;
typedef char           int8;
typedef short int      int16;
typedef int            int32;
typedef uchar          uint8;
typedef ushort         uint16;
typedef uint           uint32;

typedef float space_unit;

}

#endif
