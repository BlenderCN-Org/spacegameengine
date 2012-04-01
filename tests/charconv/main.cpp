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


#include <sge/charconv/convert.hpp>
#include <sge/charconv/create_system.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/charconv/system.hpp>
#include <sge/charconv/system_scoped_ptr.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <string>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	charconv_main
)
{
FCPPT_PP_POP_WARNING

	// TODO: adapt this to different platforms
	std::string const test(
		"馬鹿"
	);

	typedef sge::charconv::string_type<
		sge::charconv::encoding::utf8
	>::type utf8_string;

	utf8_string const utf8_test(
		test.begin(),
		test.end()
	);

	typedef sge::charconv::string_type<
		sge::charconv::encoding::utf32
	>::type utf32_string;

	sge::charconv::system_scoped_ptr const charconv_system(
		sge::charconv::create_system()
	);

	utf32_string const utf32_test(
		sge::charconv::convert<
			sge::charconv::encoding::utf32,
			sge::charconv::encoding::utf8
		>(
			*charconv_system,
			utf8_test
		)
	);

	std::wstring const out(
		utf32_test.begin(),
		utf32_test.end()
	);

	BOOST_REQUIRE(
		out == L"馬鹿"
	);
}
