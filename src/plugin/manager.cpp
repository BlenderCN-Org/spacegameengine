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
#include <sge/plugin/manager.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/plugin/detail/version_fun.hpp>
#include <sge/library/function_not_found.hpp>
#include <sge/iconv.hpp>
#include <sge/filesystem/directory_iterator.hpp>
#include <sge/filesystem/is_directory.hpp>
#include <sge/filesystem/extension.hpp>
#include <sge/text.hpp>

const char* const plugin_path =
#ifndef _MSC_VER
PLUGIN_PATH
#else
PLUGIN_PATH "/" CMAKE_INTDIR
#endif
  ;
const sge::string::const_pointer plugin_extension =
#ifdef SGE_POSIX_PLATFORM
	SGE_TEXT(".so")
#elif SGE_WINDOWS_PLATFORM
	SGE_TEXT(".dll")
#else
#error "Don't know which plugin extension to use!"
#endif
	;

sge::plugin::manager::manager()
{
	filesystem::directory_iterator const end;
	for(filesystem::directory_iterator it(iconv(plugin_path)); it != end; ++it)
	{
		if(filesystem::is_directory(*it) || filesystem::extension(*it) != plugin_extension)
			continue;

		try {
			plugins.push_back(context_base(*it));
		} catch(
			library::function_not_found const &e) {
			// ignore info loading error - it's just a DLL, not a plugin...
			// nothing to worry about (and especially nothing that justifies
			// aborting the program ...)
			if (e.func() != version_fun)
				throw;
		}
	}

	for(plugin_array::iterator it = plugins.begin(); it != plugins.end(); ++it)
		for(unsigned i = 1; i < capabilities::last_guard_; i <<= 1)
		{
			const unsigned type = it->type();
			if(type & i)
				categories[static_cast<capabilities::type>(i)].push_back(&*it);
		}
}

sge::plugin::manager::~manager()
{}
