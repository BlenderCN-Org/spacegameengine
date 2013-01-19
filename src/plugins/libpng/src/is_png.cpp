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


#include <sge/libpng/header_bytes.hpp>
#include <sge/libpng/is_png.hpp>
#include <sge/libpng/png.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <iosfwd>
#include <istream>
#include <fcppt/config/external_end.hpp>


bool
sge::libpng::is_png(
	std::istream &_stream
)
{
	std::array<
		char,
		libpng::header_bytes::value
	> buf;

	_stream.read(
		buf.data(),
		static_cast<
			std::streamsize
		>(
			buf.size()
		)
	);

	return
		_stream.gcount()
		<
		static_cast<
			std::streamsize
		>(
			buf.size()
		)
		||
		!png_sig_cmp(
			reinterpret_cast<
				png_byte *
			>(
				buf.data()
			),
			static_cast<
				png_size_t
			>(
				0
			),
			static_cast<
				png_size_t
			>(
				buf.size()
			)
		);
}
