/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../char_metric.hpp"
#include "../glyph.hpp"
#include <sge/image/view/make.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/size_type.hpp>
#include <sge/font/exception.hpp>
#include <sge/log/global.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <ostream>

sge::freetype::char_metric::char_metric(
	freetype::face &_face,
	font::char_type const _ch
)
:
	buffer_(),
	offset_(),
	x_advance_()
{
	if(
		::FT_Load_Char(
			_face.get(),
			_ch, // FIXME!
			FT_LOAD_DEFAULT
		)
	)
		throw sge::font::exception(
			FCPPT_TEXT("FT_Load_Glyph() failed!")
		);

	freetype::glyph glyph(
		_face
	);

	FT_BitmapGlyph const bmp_glyph(
		glyph.bitmap_glyph()
	);

	FT_Bitmap &bitmap(
		bmp_glyph->bitmap
	);

	offset_.x() = bmp_glyph->left;

	offset_.y() = static_cast<font::unit>(_face->size->metrics.ascender / 64 - bmp_glyph->top);

	x_advance_ = static_cast<font::unit>(_face->glyph->advance.x / 64);

	// FIXME: fix offsets and maybe those warnings
	if(offset_.x() < 0)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("x offset of character '")
				<< _ch
				<< FCPPT_TEXT("' is ")
				<< offset_.x()
				<< FCPPT_TEXT('!')
		);

	if(offset_.y() < 0)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("y offset of character '")
				<< _ch
				<< FCPPT_TEXT("' is ")
				<< offset_.y()
				<< FCPPT_TEXT('!')
		);

	// FIXME
	if(
		bitmap.pitch < 0
	)
		throw sge::exception(
			FCPPT_TEXT("FIXME: bitmap pitch < 0, case not handled!")
		);

	image::dim_type const dim(
		static_cast<
			image::dim_type::value_type
		>(
			bitmap.width
		),
		static_cast<
			image::dim_type::value_type
		>(
			bitmap.rows
		)
	);

	buffer_ = buffer_type(
		dim
	);

	image::algorithm::copy_and_convert(
		sge::image::view::make(
			static_cast<
				unsigned char const *
			>(
				bitmap.buffer
			),
			dim,
			sge::image::color::format::alpha8,
			static_cast<
				image::size_type
			>(
				bitmap.pitch - bitmap.width
			)
		),
		buffer_.view()
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
	return buffer_.view();
}

sge::font::unit
sge::freetype::char_metric::x_advance() const
{
	return x_advance_;
}
