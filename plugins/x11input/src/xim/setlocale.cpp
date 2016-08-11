/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/exception.hpp>
#include <sge/x11input/xim/setlocale.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <clocale>
#include <string>
#include <fcppt/config/external_end.hpp>


std::string
sge::x11input::xim::setlocale(
	std::string const &_what
)
{
	char const *const ret(
		::setlocale(
			LC_ALL,
			_what.c_str()
		)
	);

	if(
		ret
		==
		nullptr
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("Can't set LC_ALL to ")
				+
				fcppt::from_std_string(
					_what
				)
			};

	return
		ret;
}
