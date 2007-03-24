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


#ifndef SGE_LIBRARY_HPP_INCLUDED
#define SGE_LIBRARY_HPP_INCLUDED

#include "string.hpp"
#include "types.hpp"

#ifdef SGE_WINDOWS_PLATFORM
#include "windows.hpp"
#elif SGE_LINUX_PLATFORM
#include<dlfcn.h>
#endif

namespace sge
{

class library {
private:
#ifdef SGE_WINDOWS_PLATFORM
	HMODULE handle;
#elif SGE_LINUX_PLATFORM
	void* handle;
#endif
public:
	library(const string& n);
	~library();

	template<typename Fun>
	Fun load_function(const string& fun);

	const string& name() const;
private:
	string liberror() const;

	string n;
};

}

#include "./detail/library_impl.hpp"

#endif
