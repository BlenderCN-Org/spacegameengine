/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/config/exception.hpp>
#include <sge/src/config/try_create_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/create_directories_recursive_exn.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>



boost::filesystem::path const
sge::config::try_create_path(
	boost::filesystem::path const &_path
)
{
	if(
		!boost::filesystem::exists(
			_path
		)
	)
		fcppt::filesystem::create_directories_recursive_exn(
			_path
		);

	if(
		!boost::filesystem::is_directory(
			_path
		)
	)
		throw sge::config::exception(
			fcppt::filesystem::path_to_string(
				_path
			)
			+ FCPPT_TEXT(" is not a directory!")
		);

	return _path;
}
