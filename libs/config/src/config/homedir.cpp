/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/config/getenv_exn.hpp>
#include <sge/config/homedir.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


boost::filesystem::path
sge::config::homedir()
{
#if defined(FCPPT_CONFIG_POSIX_PLATFORM)
	return
		sge::config::getenv_exn(
			FCPPT_TEXT("HOME")
		);
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	return
		sge::config::getenv_exn(
			FCPPT_TEXT("USERPROFILE")
		);
#else
#error "Don't know how to get the homedir"
#endif
}
