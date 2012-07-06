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


#include <sge/cegui/from_cegui_string.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/optional_pitch.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <sge/src/cegui/from_cegui_size.hpp>
#include <sge/src/cegui/optional_sizef.hpp>
#include <sge/src/cegui/prefix.hpp>
#include <sge/src/cegui/texture.hpp>
#include <sge/src/cegui/to_absolute_path.hpp>
#include <sge/src/cegui/to_cegui_size.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/config/external_begin.hpp>
//#include <CEGUIImageCodec.h>
//#include <CEGUIResourceProvider.h>
#include <CEGUI/Size.h>
#include <CEGUI/String.h>
#include <CEGUI/Texture.h>
#include <CEGUI/Vector.h>
#include <fcppt/config/external_end.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("texture")
)

sge::cegui::texture::texture(
	sge::cegui::texture_parameters const &_texture_parameters,
	sge::renderer::texture::capabilities_field const &_caps,
	sge::cegui::optional_sizef const &_size,
	CEGUI::String const &_name
)
:
	texture_parameters_(
		_texture_parameters
	),
	caps_(
		_caps
	),
	texture_(),
	size_(
		_size
	),
	name_(
		_name
	),
	texel_scaling_(
		1.f,
		1.f
	)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture(")
			<< this
			<< FCPPT_TEXT(")::texture()")
	);
}

sge::cegui::texture::~texture()
{
}

sge::renderer::texture::planar &
sge::cegui::texture::impl()
{
	return
		*texture_;
}

void
sge::cegui::texture::create_from_view(
	sge::image2d::view::const_object const &_view
)
{
	size_ =
		sge::cegui::optional_sizef(
			sge::cegui::to_cegui_size<
				float // TODO
			>(
				sge::image2d::view::size(
					_view
				)
			)
		);

	texel_scaling_ =
		CEGUI::Vector2f(
			static_cast<
				sge::cegui::unit
			>(
				1
			)
			/
			size_->d_width,
			static_cast<
				sge::cegui::unit
			>(
				1
			)
			/
			size_->d_height
		);

	texture_.take(
		sge::renderer::texture::create_planar_from_view(
			texture_parameters_.renderer(),
			_view,
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags::none
		)
	);
}

bool
sge::cegui::texture::empty() const
{
	return
		!size_;
}

CEGUI::String const  &
sge::cegui::texture::getName() const
{
	return
		name_;
}

CEGUI::Sizef const &
sge::cegui::texture::getSize() const
{
	FCPPT_ASSERT_PRE(
		size_
	);

	return
		*size_;
}

CEGUI::Sizef const &
sge::cegui::texture::getOriginalDataSize() const
{
	return
		this->getSize();
}

CEGUI::Vector2f const &
sge::cegui::texture::getTexelScaling() const
{
	return
		texel_scaling_;
}

void
sge::cegui::texture::loadFromFile(
	CEGUI::String const &_filename,
	CEGUI::String const &_resource_group
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture(")
			<< this
			<< FCPPT_TEXT(")::loadFromFile(")
			<< sge::cegui::from_cegui_string(
				_filename,
				texture_parameters_.charconv_system()
			)
			<< FCPPT_TEXT(", ")
			<< sge::cegui::from_cegui_string(
				_resource_group,
				texture_parameters_.charconv_system()
			)
			<< FCPPT_TEXT(")"));

	this->create_from_view(
		texture_parameters_.image_system().load(
			sge::cegui::to_absolute_path(
				texture_parameters_.charconv_system(),
				texture_parameters_.prefix(),
				_filename
			)
		)->view()
	);
}

void
sge::cegui::texture::loadFromMemory(
	void const * const _buffer,
	CEGUI::Sizef const &_buffer_size,
	CEGUI::Texture::PixelFormat const _pixel_format
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture(")
			<< this
			<< FCPPT_TEXT(")::loadFromMemory(")
			<< sge::cegui::from_cegui_size<
				sge::renderer::dim2
			>(
				_buffer_size
			)
			<< FCPPT_TEXT(')')
	);

	FCPPT_ASSERT_PRE(
		this->empty()
	);

	this->create_from_view(
		sge::image2d::view::make_const(
			static_cast<
				sge::image::const_raw_pointer
			>(
				_buffer
			),
			sge::cegui::from_cegui_size<
				sge::image2d::dim
			>(
				_buffer_size
			),
			// TODO: own function!
			_pixel_format == PF_RGB
			?
				sge::image::color::format::rgb8
			:
				sge::image::color::format::rgba8
			,
			sge::image2d::view::optional_pitch()
		)
	);
}

void
sge::cegui::texture::blitFromMemory(
	void *const _source,
	CEGUI::Rectf const &_area
)
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("texture::blitFromMemory() is not implemented yet")
	);
}

void
sge::cegui::texture::blitToMemory(
	void *const _data
)
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("texture::blitToMemory() is not implemented yet")
	);
}

bool
sge::cegui::texture::isPixelFormatSupported(
	CEGUI::Texture::PixelFormat const _format
) const
{
	switch(
		_format
	)
	{
	case CEGUI::Texture::PF_RGB:
	case CEGUI::Texture::PF_RGBA:
		return true;
	case CEGUI::Texture::PF_RGBA_4444:
	case CEGUI::Texture::PF_RGB_565:
	case CEGUI::Texture::PF_PVRTC2:
	case CEGUI::Texture::PF_PVRTC4:
	case CEGUI::Texture::PF_RGB_DXT1:
	case CEGUI::Texture::PF_RGBA_DXT1:
	case CEGUI::Texture::PF_RGBA_DXT3:
	case CEGUI::Texture::PF_RGBA_DXT5:
		return false;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
