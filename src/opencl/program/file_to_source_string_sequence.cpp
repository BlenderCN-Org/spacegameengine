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


#include <sge/opencl/program/file_to_source_string_sequence.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::opencl::program::source_string_sequence const
sge::opencl::program::file_to_source_string_sequence(
	boost::filesystem::path const &_path
)
{
	return
		sge::opencl::program::source_string_sequence{
			fcppt::io::stream_to_string(
				*fcppt::make_unique_ptr<
					boost::filesystem::ifstream
				>(
					_path
				)
			)
		};
}
