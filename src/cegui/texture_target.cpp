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


#include <sge/image/color/predef.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/color_buffer/optional_surface_ref.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/optional_object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/optional_offscreen_ref.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <sge/src/cegui/from_cegui_rect.hpp>
#include <sge/src/cegui/from_cegui_size.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/texture.hpp>
#include <sge/src/cegui/texture_target.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/GeometryBuffer.h>
#include <CEGUI/RenderQueue.h>
#include <CEGUI/String.h>
#include <fcppt/config/external_end.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("texture_target")
)

sge::cegui::texture_target::texture_target(
	sge::cegui::texture_parameters const &_texture_parameters,
	sge::cegui::optional_render_context_ref const &_render_context
)
:
	texture_parameters_(
		_texture_parameters
	),
	target_(
		texture_parameters_.renderer().create_target()
	),
	render_context_(
		_render_context
	),
	texture_(),
	// This is exactly what cegui does and it avoids certain bugs :/
	area_(
		0,
		0,
		0,
		0
	),
	is_inverted_(
		_texture_parameters.renderer().caps().render_target_inverted()
	),
	transform_state_()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture_target(")
			<< this
			<< FCPPT_TEXT(")::texture_target")
	);
}

sge::cegui::texture_target::~texture_target()
{
}

void
sge::cegui::texture_target::draw(
	CEGUI::GeometryBuffer const &_buffer
)
{
	if(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			texture_
		)->empty()
	)
		return;

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture_target(")
			<< this
			<< FCPPT_TEXT(")::draw(GeometryBuffer)")
	);

	_buffer.draw();
}

void
sge::cegui::texture_target::draw(
	CEGUI::RenderQueue const &_queue
)
{
	if(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			texture_
		)->empty()
	)
		return;

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture_target(")
			<< this
			<< FCPPT_TEXT(")::draw(RenderQueue)")
	);

	_queue.draw();
}

void
sge::cegui::texture_target::setArea(
	CEGUI::Rectf const &_area
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture_target(")
			<< this
			<< FCPPT_TEXT(")::setArea(")
			<< sge::cegui::from_cegui_rect<
				sge::renderer::pixel_rect
			>(
				_area
			)
			<< FCPPT_TEXT(')')
	);

	area_ =
		_area;

	if(
		area_.getWidth()
		*
		area_.getHeight()
		<
		0.01f
	)
	{
		transform_state_ =
			sge::renderer::state::ffp::transform::optional_object_unique_ptr();

		return;
	}

	transform_state_ =
		sge::renderer::state::ffp::transform::optional_object_unique_ptr(
			texture_parameters_.renderer().create_transform_state(
				sge::renderer::state::ffp::transform::parameters(
					sge::renderer::projection::orthogonal(
						sge::cegui::from_cegui_rect<
							sge::renderer::projection::rect
						>(
							area_
						),
						sge::renderer::projection::near(
							0.f
						),
						sge::renderer::projection::far(
							2.f
						)
					)
				)
			)
		);
}

CEGUI::Rectf const &
sge::cegui::texture_target::getArea() const
{
	return
		area_;
}

bool
sge::cegui::texture_target::isImageryCache() const
{
	return
		true;
}

void
sge::cegui::texture_target::activate()
{
	if(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			texture_
		)->empty()
	)
		return;

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture_target(")
			<< this
			<< FCPPT_TEXT(")::activate()")
	);

	sge::renderer::context::ffp &render_context(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			render_context_
		)
	);

	render_context.offscreen_target(
		sge::renderer::target::optional_offscreen_ref(
			*target_
		)
	);

	target_->viewport(
		sge::renderer::target::viewport(
			sge::cegui::from_cegui_rect<
				sge::renderer::pixel_rect
			>(
				area_
			)
		)
	);

	render_context.transform(
		sge::renderer::state::ffp::transform::mode::projection,
		sge::renderer::state::ffp::transform::const_optional_object_ref(
			*FCPPT_ASSERT_OPTIONAL_ERROR(
				transform_state_
			)
		)
	);
}

void
sge::cegui::texture_target::deactivate()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture_target(")
			<< this
			<< FCPPT_TEXT(")::deactivate()")
	);

	if(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			texture_
		)->empty()
	)
		return;

	sge::renderer::context::ffp &render_context(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			render_context_
		)
	);

	render_context.transform(
		sge::renderer::state::ffp::transform::mode::projection,
		sge::renderer::state::ffp::transform::const_optional_object_ref()
	);

	render_context.offscreen_target(
		sge::renderer::target::optional_offscreen_ref()
	);
}

void
sge::cegui::texture_target::unprojectPoint(
	CEGUI::GeometryBuffer const &,
	CEGUI::Vector2f const &,
	CEGUI::Vector2f &
) const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("texture_target::unprojectPoint not implemented yet")
	);
}

void
sge::cegui::texture_target::clear()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture_target(")
			<< this
			<< FCPPT_TEXT(")::clear()")
	);

	sge::cegui::texture &texture(
		*FCPPT_ASSERT_OPTIONAL_ERROR(
			texture_
		)
	);

	// TODO: Use optionals here
	if(
		texture.empty()
	)
		return;

	// Make sure we clear everything

	sge::renderer::pixel_rect const rect(
		sge::renderer::pixel_rect::vector::null(),
		fcppt::math::dim::structure_cast<
			sge::renderer::pixel_rect::dim,
			fcppt::cast::size_fun
		>(
			fcppt::math::dim::to_signed(
				texture.impl().size()
			)
		)
	);

	target_->viewport(
		sge::renderer::target::viewport(
			rect
		)
	);

	target_->scissor_area(
		sge::renderer::target::scissor_area(
			rect
		)
	);

	target_->clear(
		sge::renderer::clear::parameters()
		.back_buffer(
			sge::image::color::predef::transparent()
		)
	);
}

CEGUI::Texture &
sge::cegui::texture_target::getTexture() const
{
	return
		*FCPPT_ASSERT_OPTIONAL_ERROR(
			texture_
		);
}

void
sge::cegui::texture_target::declareRenderSize(
	CEGUI::Sizef const &_size
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture_target(")
			<< this
			<< FCPPT_TEXT(")::declareRenderSize(")
			<< sge::cegui::from_cegui_size<
				sge::renderer::dim2
			>(
				_size
			)
			<< FCPPT_TEXT(')')
	);

	this->setArea(
		CEGUI::Rectf(
			area_.getPosition(),
			_size
		)
	);

	CEGUI::String const texture_name(
		"sge texture target"
	);

	// The size here could be (0,0), for example if the viewport hasn't
	// been initialized yet. If that's the case, create an empty texture.

	texture_ =
		optional_texture_unique_ptr(
			sge::cegui::from_cegui_size<
				sge::renderer::dim2
			>(
				_size
			)
			==
			sge::renderer::dim2::null()
			?
				fcppt::make_unique_ptr<
					sge::cegui::texture
				>(
					texture_parameters_,
					texture_name
				)
			:
				fcppt::make_unique_ptr<
					sge::cegui::texture
				>(
					texture_parameters_,
					texture_name,
					_size,
					sge::renderer::texture::capabilities_field{
						sge::renderer::texture::capabilities::render_target
					}
				)
		);

	// TODO: Use optionals here
	if(
		texture_.get_unsafe()->empty()
	)
		return;

	target_->color_surface(
		sge::renderer::color_buffer::optional_surface_ref(
			texture_.get_unsafe()->impl().level(
				sge::renderer::texture::mipmap::level(
					0u
				)
			)
		),
		sge::renderer::target::surface_index(
			0u
		)
	);

	this->clear();
}

bool
sge::cegui::texture_target::isRenderingInverted() const
{
	return
		is_inverted_.get();
}
