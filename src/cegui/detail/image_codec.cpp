/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/cegui/detail/image_codec.hpp>
#include <sge/cegui/detail/texture.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/optional_extension.hpp>
#include <sge/const_raw_range.hpp>
#include <sge/image2d/file.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/optional_impl.hpp>

sge::cegui::detail::image_codec::image_codec(
	sge::image2d::multi_loader &_image_loader)
:
	CEGUI::ImageCodec(
		"sge image codec"),
	image_loader_(
		_image_loader)
{
}

sge::cegui::detail::image_codec::~image_codec()
{
}

CEGUI::Texture *
sge::cegui::detail::image_codec::load(
	CEGUI::RawDataContainer const &data,
	CEGUI::Texture *result_texture)
{
	FCPPT_ASSERT(
		result_texture);

	dynamic_cast<texture &>(*result_texture).create_from_view(
		image_loader_.load_raw(
			sge::const_raw_range(
				data.getDataPtr(),
				data.getDataPtr() + data.getSize()),
			sge::optional_extension())->view());

	return result_texture;
}

sge::image2d::multi_loader &
sge::cegui::detail::image_codec::loader() const
{
	return image_loader_;
}
