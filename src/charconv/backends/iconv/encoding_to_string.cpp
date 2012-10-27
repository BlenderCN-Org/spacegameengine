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


#include <sge/charconv/encoding.hpp>
#include <sge/src/charconv/backends/iconv/encoding_string.hpp>
#include <sge/src/charconv/backends/iconv/encoding_to_string.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/endianness/is_little_endian.hpp>


sge::charconv::backends::iconv::encoding_string const
sge::charconv::backends::iconv::encoding_to_string(
	sge::charconv::encoding::type const _encoding
)
{
	switch(
		_encoding
	)
	{
	case sge::charconv::encoding::utf8:
		return "UTF-8";
	case sge::charconv::encoding::utf16:
		return
			fcppt::endianness::is_little_endian()
			?
				"UTF-16LE"
			:
				"UTF-16BE";
	case sge::charconv::encoding::utf32:
		return
			fcppt::endianness::is_little_endian()
			?
				"UTF-32LE"
			:
				"UTF-32BE";
	case sge::charconv::encoding::wchar:
		return "WCHAR_T";
	case sge::charconv::encoding::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
