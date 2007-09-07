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


#include "../types.hpp"
#include "../exception.hpp"
#include "../time.hpp"

#ifdef SGE_LINUX_PLATFORM
#include <sys/time.h>
#elif SGE_WINDOWS_PLATFORM
#include "../windows.hpp"
#endif

sge::time_type sge::time()
{
#ifdef SGE_LINUX_PLATFORM
	struct timeval tv;
	struct timezone tz;
	if(gettimeofday(&tv,&tz) != 0)
		throw sge::exception("gettimeofday() failed");
	return static_cast<time_type>(tv.tv_sec * 1000 + tv.tv_usec / 1000);
#elif SGE_WINDOWS_PLATFORM
	return static_cast<time_type>(GetTickCount());
#endif
}
