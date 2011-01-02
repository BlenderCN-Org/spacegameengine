/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../system.hpp"
#include "../converter.hpp"
#include "../encoding_to_string.hpp"
#include <fcppt/make_shared_ptr.hpp>

sge::iconv::system::system()
{
}

sge::iconv::system::~system()
{
}

sge::charconv::converter_ptr const
sge::iconv::system::create_converter(
	charconv::source_encoding const _source,
	charconv::dest_encoding const _dest
)
{
	return
		fcppt::make_shared_ptr<
			iconv::converter
		>(
			iconv::encoding_to_string(
				_source.get()
			),
			iconv::encoding_to_string(
				_dest.get()
			)
		);
}
