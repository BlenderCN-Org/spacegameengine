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
#include <sge/charconv/encoding_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string const
sge::charconv::encoding_to_string(
	sge::charconv::encoding const _encoding
)
{
#define SGE_CHARCONV_ENCODING_CASE(\
	name\
)\
case sge::charconv::encoding::name:\
	return FCPPT_TEXT(#name)

	switch(
		_encoding
	)
	{
		SGE_CHARCONV_ENCODING_CASE(
			utf8
		);
		SGE_CHARCONV_ENCODING_CASE(
			utf16
		);
		SGE_CHARCONV_ENCODING_CASE(
			utf32
		);
		SGE_CHARCONV_ENCODING_CASE(
			wchar
		);
		case sge::charconv::encoding::size:
			break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
