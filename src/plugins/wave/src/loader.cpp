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


#include "../file.hpp"
#include "../loader.hpp"
#include <sge/audio/exception.hpp>
#include <sge/log/headers.hpp>
#include <ostream>

sge::audio::file_ptr const
sge::wave::loader::load(
	filesystem::path const &filename)
{
	return audio::file_ptr(new file(filename));
}

bool sge::wave::loader::is_valid_file(
	filesystem::path const &filename) const
{
	try 
	{
		file const file_(filename);
		SGE_LOG_DEBUG(log::global(),log::_1 << "wave file info: " << file_.to_string());
	} 
	catch (audio::exception const &e) 
	{
		SGE_LOG_DEBUG(log::global(),log::_1 << "couldn't load " << filename << ": " << e.what());
		return false;
	}
	return true;
}
