/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/media/optional_path.hpp>
#include <sge/media/file_exception_string.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


fcppt::string
sge::media::file_exception_string(
	sge::media::optional_path const &_opt_path,
	fcppt::string const &_message
)
{
	return
		fcppt::maybe(
			_opt_path,
			[
				&_message
			]
			{
				return
					FCPPT_TEXT("stream: ")
					+
					_message;
			},
			[
				&_message
			](
				boost::filesystem::path const &_path
			)
			{
				return
					FCPPT_TEXT("\"")
					+
					fcppt::filesystem::path_to_string(
						_path
					)
					+
					FCPPT_TEXT("\": ")
					+
					_message;
			}
		);
}
