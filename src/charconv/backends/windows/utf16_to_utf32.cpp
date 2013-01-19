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


#include <sge/charconv/conversion_status.hpp>
#include <sge/charconv/input_range.hpp>
#include <sge/charconv/output_range.hpp>
#include <sge/charconv/raw_value.hpp>
#include <sge/src/charconv/backends/windows/utf16_to_utf32.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <fcppt/config/external_end.hpp>


sge::charconv::backends::windows::utf16_to_utf32::utf16_to_utf32()
{
}

sge::charconv::backends::windows::utf16_to_utf32::~utf16_to_utf32()
{
}

sge::charconv::conversion_status
sge::charconv::backends::windows::utf16_to_utf32::convert(
	sge::charconv::input_range &_input,
	sge::charconv::output_range &_output
)
{
	// Let the system resize the output until we've got double the input size
	if(_output.size() < (static_cast<charconv::output_range::difference_type>(2)*_input.size()))
		return sge::charconv::conversion_status::output_too_small;

	if (_input.size() % static_cast<charconv::output_range::difference_type>(2) != 0)
		return sge::charconv::conversion_status::invalid_input;

	while(_input.begin() != _input.end())
	{
		typedef
		std::uint16_t
		utf16;

		typedef
		std::uint32_t
		utf32;

		// Instead of operating on the ranges themselves, put everything
		// in small arrays, which are must prettier to handle
		std::array<charconv::raw_value,2> const lobytes{{
			*_input.begin(),
			(*std::next(_input.begin()))
		}};

		std::array<charconv::raw_value,4> output_bytes{{
			0,0,0,0
		}};

		_input.advance_begin(
			static_cast<charconv::input_range::difference_type>(
				2));

		utf16 const lo =
			static_cast<utf16>(
				(lobytes[1] << 8) | lobytes[0]);

		// We've got just one pair of bytes, no surrogates (taken from
		// http://en.wikipedia.org/wiki/UTF-16/UCS-2)
		if(lo < static_cast<utf16>(0xD7FF) || lo > static_cast<utf16>(0xE000))
		{
			// assign two bytes by hand
			output_bytes[0] = lobytes[0];
			output_bytes[1] = lobytes[1];
		}
		else
		{
			// Doesn't work because size returns difference_type instead of size_type, FFFFFUUUUUUUU
			//if (_input.size() < static_cast<charconv::input_range::size_type>(2))
			if (_input.size() < static_cast<charconv::input_range::difference_type>(2))
				return charconv::conversion_status::invalid_input;

			std::array<charconv::raw_value,2> const hibytes{{
				*_input.begin(),
				(*std::next(_input.begin()))
			}};

			_input.advance_begin(
				static_cast<charconv::input_range::difference_type>(
					2));

			utf16 const hi =
				static_cast<utf16>(
					hibytes[1] << 8 | hibytes[0]);

			// Explanation: When you convert a Unicode code point called X,
			// which is above 0xffff, to two utf-16 surrogates hi and lo, the
			// following steps are taken:
			//
			// X' = X - 0x10000
			// hi = top_ten(X') + 0xd800
			// lo = lower_ten(X') + 0xdc00
			//
			// So to invert this process, starting with hi and lo:
			//
			// top_ten(X') = hi - 0xd800
			// lower_ten(X') = lo - 0xdc00
			// X' = top_ten(X') << 10 + lower_ten(X')
			// X = X' + 0x10000
			utf32 const result =
				static_cast<utf32>(
					static_cast<utf32>(
						((lo - static_cast<utf32>(0xd800)) << 10) |
						(hi - static_cast<utf32>(0xdc00))) +
						static_cast<utf32>(0x10000));

			for (std::size_t i = 0; i < 4; ++i)
				output_bytes[i] = static_cast<charconv::raw_value>(result >> (i*8) & 0xff);
		}

		std::copy(
			output_bytes.begin(),
			output_bytes.end(),
			_output.begin());

		_output.advance_begin(
			static_cast<sge::charconv::output_range::difference_type>(
				4));
	}

	return sge::charconv::conversion_status::ok;
}
