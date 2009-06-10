/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../freetype.hpp"
#include "../face.hpp"
#include "../glyph.hpp"
#include "../char_metric.hpp"
#include <sge/image/algorithm/transform.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/log/headers.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/gil/algorithm.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/bind.hpp>
#include <ostream>

namespace
{

void converter(
	boost::gil::gray8_pixel_t const &src,
	sge::image::color::rgba8 &dest)
{
	dest = sge::image::color::rgba8(
		255,
		255,
		255,
		src
	);
}

}

sge::freetype::char_metric::char_metric(
	face &face_,
	char_type const ch)
:
	buffer(),
	offset_()
{
	if(FT_Load_Char(face_.get(), ch, FT_LOAD_DEFAULT))
		throw exception(SGE_TEXT("FT_Load_Glyph() failed!"));

	glyph glyph_(face_);
	FT_BitmapGlyph bmp_glyph = glyph_.bitmap_glyph();

	FT_Bitmap& bitmap = bmp_glyph->bitmap;
	
	offset_.x() = bmp_glyph->left;
	offset_.y() = static_cast<font::unit>(face_->size->metrics.ascender / 64 - bmp_glyph->top);
	x_advance_ = static_cast<font::unit>(face_->glyph->advance.x / 64);

	// FIXME: fix offsets and maybe those warnings
	if(offset_.x() < 0)
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT("x offset of character '")
				<< ch
				<< SGE_TEXT("' is ")
				<< offset_.x()
				<< SGE_TEXT('!'));
	if(offset_.y() < 0)
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT("y offset of character '")
				<< ch
				<< SGE_TEXT("' is ")
				<< offset_.y()
				<< SGE_TEXT('!'));

	boost::gil::gray8c_view_t src(
		boost::gil::interleaved_view(
			bitmap.width,
			bitmap.rows,
			reinterpret_cast<
				boost::gil::gray8_pixel_t const *
			>(
				bitmap.buffer
			),
			bitmap.pitch
		)
	);
	
	buffer.recreate(
		bitmap.width,
		bitmap.rows
	);

	sge::image::algorithm::transform(
		src,
		boost::gil::view(
			buffer
		),
		boost::bind(
			converter,
			_1,
			_2
		)
	);
}

sge::freetype::char_metric::~char_metric()
{}

sge::font::pos const
sge::freetype::char_metric::offset() const
{
	return offset_;
}

sge::font::const_image_view const
sge::freetype::char_metric::pixmap() const
{
	return boost::gil::const_view(
		buffer
	);
}

sge::font::unit sge::freetype::char_metric::x_advance() const
{
	return x_advance_;
}
