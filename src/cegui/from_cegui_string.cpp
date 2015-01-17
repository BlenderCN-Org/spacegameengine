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


#include <sge/cegui/from_cegui_string.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <CEGUI/String.h>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


fcppt::string
sge::cegui::from_cegui_string(
	CEGUI::String const &_string
)
{
	typedef
	sge::charconv::string_type
	<
		sge::charconv::encoding::utf32
	>
	source_string;

	static_assert(
		std::is_same
		<
			source_string::value_type,
			CEGUI::utf32
		>::value,
		"CEGUI's string must use utf32"
	);

	typedef
	sge::charconv::string_type
	<
		sge::charconv::encoding::wchar
	>
	dest_string;

	dest_string const dest(
		sge::charconv::convert
		<
			sge::charconv::encoding::wchar,
			sge::charconv::encoding::utf32
		>(
			source_string(
				_string.begin(),
				_string.end()
			)
		)
	);

	return
		fcppt::from_std_wstring(
			dest
		);
}
