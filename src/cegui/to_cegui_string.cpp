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


#include <sge/cegui/to_cegui_string.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <fcppt/string.hpp>
#include <fcppt/to_std_wstring.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <CEGUI/String.h>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


CEGUI::String const
sge::cegui::to_cegui_string(
	fcppt::string const &_string,
	sge::charconv::system &_charconv
)
{
	// This is here so that the CEGUI::String constructor with a zero
	// length null terminated utf8 string doesn't get used, because it
	// crashes under gcc-4.7
	if(
		_string.empty()
	)
		return CEGUI::String();

	typedef
	sge::charconv::string_type
	<
		sge::charconv::encoding::utf8
	>::type
	utf8_string;

	static_assert(
		std::is_same
		<
			utf8_string::value_type,
			CEGUI::utf8
		>::value,
		"CEGUI's string must use utf32"
	);

	return
		CEGUI::String(
			sge::charconv::convert
			<
				sge::charconv::encoding::utf8,
				sge::charconv::encoding::wchar
			>(
				_charconv,
				fcppt::to_std_wstring(
					_string
				)
			).c_str()
		);
}
