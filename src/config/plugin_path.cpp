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


#include "find_own_path.hpp"
#include <sge/config/plugin_path.hpp>
#include <sge/iconv.hpp>
#include <sge/text.hpp>
#include <boost/assign/list_of.hpp>

sge::filesystem::path const
sge::config::plugin_path()
{
	static filesystem::path const ret(
		find_own_path(
			FCPPT_TEXT("plugin_path"),
			boost::assign::list_of(
				iconv(
// TODO: why did we do this?
#ifndef _MSC_VER
					PLUGIN_PATH
#else
					PLUGIN_PATH "/" CMAKE_INTDIR
#endif
				)
			)
		)
	);

	return ret;
}
