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



#include "../file.hpp"
#include "../loader.hpp"
#include <sge/audio/exception.hpp>
#include <sge/log/headers.hpp>
#include <sge/text.hpp>

sge::audio::file_ptr const
sge::vorbis::loader::load(
	filesystem::path const &filename)
{
	return audio::file_ptr(new file(filename));
}

bool sge::vorbis::loader::is_valid_file(
	filesystem::path const &filename) const
{
	try { 
		file const file_(filename);
	} catch (audio::exception const &) {
		return false;
	}
	SGE_LOG_DEBUG(log::global(),log::_1 << SGE_TEXT("successfully loaded vorbis file"));
	return true;
}
