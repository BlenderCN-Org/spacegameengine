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


#include <sge/image/color/element_count.hpp>
#include <sge/libpng/bit_depth_from_format.hpp>
#include <sge/libpng/byte_vector.hpp>
#include <sge/libpng/bytes_per_pixel.hpp>
#include <sge/libpng/color_type_from_format.hpp>
#include <sge/libpng/error_context.hpp>
#include <sge/libpng/file_rep.hpp>
#include <sge/libpng/info.hpp>
#include <sge/libpng/make_row_vector.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/row_vector.hpp>
#include <sge/libpng/to_sge_format.hpp>
#include <sge/libpng/write.hpp>
#include <sge/libpng/write_context.hpp>
#include <sge/libpng/write_ptr.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <climits>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


void
sge::libpng::write(
	std::ostream &_stream,
	sge::media::optional_name const &_name,
	sge::libpng::file_rep const &_rep
)
{
	sge::libpng::error_context error_context{
		_name
	};

	sge::libpng::write_ptr const write_ptr(
		error_context
	);

	sge::libpng::info const info(
		write_ptr.ptr()
	);

	sge::libpng::write_context context(
		_name,
		_stream,
		write_ptr
	);

	::png_set_IHDR(
		write_ptr.ptr(),
		info.get(),
		fcppt::cast::size<
			png_uint_32
		>(
			_rep.size().w()
		),
		fcppt::cast::size<
			png_uint_32
		>(
			_rep.size().h()
		),
		sge::libpng::bit_depth_from_format(
			_rep.format()
		),
		sge::libpng::color_type_from_format(
			_rep.format()
		),
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
	);

	::png_write_info(
		write_ptr.ptr(),
		info.get()
	);

	sge::libpng::bytes_per_pixel const bytes_per_pixel(
		sge::image::color::element_count(
			sge::libpng::to_sge_format(
				_rep.format()
			)
		)
		*
		fcppt::cast::to_unsigned(
			sge::libpng::bit_depth_from_format(
				_rep.format()
			)
		)
		/
		CHAR_BIT
	);

	sge::libpng::row_vector row_ptrs(
		sge::libpng::make_row_vector(
			_rep.size(),
			const_cast<
				png_bytep
			>(
				_rep.bytes().data()
			),
			bytes_per_pixel
		)
	);

	// FIXME: Use transforms here!
	::png_write_image(
		write_ptr.ptr(),
		row_ptrs.data()
	);

	::png_write_end(
		write_ptr.ptr(),
		info.get()
	);
}
