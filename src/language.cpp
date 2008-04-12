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


#include <sge/config.h>
#include <sge/language.hpp>
#include <sge/exception.hpp>

#ifdef SGE_WINDOWS_PLATFORM
#include <sge/win32_conv.hpp>
#include <sge/windows.hpp>
#include <boost/array.hpp>
#else
#include <sge/iconv.hpp>
#include <cstdlib>
#endif

sge::string sge::language()
{
#ifdef SGE_LINUX_PLATFORM
	const char* const p = std::getenv("LANG");
	if(!p)
		throw exception(SGE_TEXT("LANG not set! Unable to detect OS language!"));
	return iconv(p);
#elif SGE_WINDOWS_PLATFORM
	boost::array<TCHAR, 128> buf;
	if(GetLocaleInfo(GetSystemDefaultLCID(), LOCALE_SLANGUAGE, buf.c_array(), static_cast<int>(buf.size())) == 0)
		throw exception(SGE_TEXT("GetLocaleInfo() failed!"));
	return win_str_to_sge(buf.data());
#endif
}
