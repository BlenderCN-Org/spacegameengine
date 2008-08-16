/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/iostream.hpp>
#include <boost/gil/algorithm.hpp>
#include <boost/gil/typedefs.hpp>
#include <ostream>
#include <cassert>

sge::ft::char_metric::char_metric(
	face &face_,
	char_type const ch)
{
	if(FT_Load_Char(face_.get(), ch, FT_LOAD_DEFAULT))
		throw exception(SGE_TEXT("FT_Load_Glyph() failed!"));

	glyph glyph_(face_);
	FT_BitmapGlyph bmp_glyph = glyph_.bitmap_glyph();

	FT_Bitmap& bitmap = bmp_glyph->bitmap;
	
	offset_.x() = bmp_glyph->left;
	offset_.y() = face_->ascender / 64 - bmp_glyph->top; // FIXME: why are the ascenders so big?
	x_advance_ = static_cast<font::unit>(face_->glyph->advance.x / 64);

	// FIXME: fix offsets and maybe those warnings
	if(offset_.x() < 0)
		cerr << SGE_TEXT("warning: x offset of character '")
		     << ch
		     << SGE_TEXT("' is ")
		     << offset_.x()
		     << SGE_TEXT("!\n");
	if(offset_.y() < 0)
		cerr << SGE_TEXT("warning: y offset of character '")
		     << ch
		     << SGE_TEXT("' is ")
		     << offset_.y()
		     << SGE_TEXT("!\n");

	boost::gil::gray8c_view_t src(
		boost::gil::interleaved_view(
			bitmap.width,
			bitmap.rows,
			reinterpret_cast<boost::gil::gray8_pixel_t const *>(
				bitmap.buffer),
			bitmap.pitch));
	
	buffer.recreate(bitmap.width, bitmap.rows);

	boost::gil::copy_pixels(src, boost::gil::view(buffer));
}

sge::font::pos const sge::ft::char_metric::offset() const
{
	return offset_;
}

sge::font::const_image_view const
sge::ft::char_metric::pixmap() const
{
	return boost::gil::const_view(buffer);
}

sge::font::unit sge::ft::char_metric::x_advance() const
{
	return x_advance_;
}
