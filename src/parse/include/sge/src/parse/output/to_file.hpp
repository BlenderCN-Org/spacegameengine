/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_PARSE_OUTPUT_TO_FILE_HPP_INCLUDED
#define SGE_SRC_PARSE_OUTPUT_TO_FILE_HPP_INCLUDED

#include <sge/parse/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ofstream.hpp>


namespace sge
{
namespace parse
{
namespace output
{

template<
	typename Data
>
bool
to_file(
	fcppt::filesystem::path const &path,
	Data const &data
)
{
	fcppt::io::ofstream ofs(
		path,
		std::ios_base::binary
	);

	if(
		!ofs.is_open()
	)
		throw parse::exception(
			FCPPT_TEXT("Opening ")
			+ fcppt::filesystem::path_to_string(
				path
			)
			+ FCPPT_TEXT(" failed!")
		);

	return
		SGE_PARSE_DETAIL_TO_STREAM_NAMESPACE :: to_stream(
			ofs,
			data
		);
#undef SGE_PARSE_DETAIL_TO_STREAM_NAMESPACE
}

}
}
}

#endif
