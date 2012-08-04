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


#include <sge/font/object.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/rect.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single_impl.hpp>
#include <sge/sprite/buffers/with_declaration_impl.hpp>
#include <sge/sprite/geometry/update_one.hpp>
#include <sge/sprite/render/matrix_options.hpp>
#include <sge/sprite/render/options.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <sge/sprite/render/range_with_options.hpp>
#include <sge/sprite/render/state_options.hpp>
#include <sge/sprite/render/vertex_options.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/scoped_planar_lock.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/src/font/draw/detail/static_text_impl.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::font::draw::detail::static_text_impl::static_text_impl(
	sge::renderer::device &_renderer,
	sge::font::object &_font,
	sge::font::text_parameters const &_text_parameters
)
:
	renderer_(
		_renderer
	),
	font_(
		_font
	),
	string_(),
	text_parameters_(
		_text_parameters
	),
	texture_(),
	texture_part_(),
	text_(),
	rect_(
		sge::font::rect::null()
	),
	sprite_buffers_(
		_renderer,
		sge::sprite::buffers::option::static_
	),
	sprite_(),
	sprite_range_()
{
}

sge::font::draw::detail::static_text_impl::~static_text_impl()
{
}

void
sge::font::draw::detail::static_text_impl::draw(
	sge::renderer::context::object &_context
)
{
	// TODO: make it possible to render this differently
	sge::sprite::render::range_with_options<
		sge::sprite::render::options<
			sge::sprite::render::matrix_options::set,
			sge::sprite::render::state_options::set,
			sge::sprite::render::vertex_options::declaration_and_buffer
		>
	>(
		sge::sprite::render::parameters(
			_context,
			sprite_buffers_.parameters().vertex_declaration()
		),
		sprite_range_
	);
}

void
sge::font::draw::detail::static_text_impl::string(
	sge::font::string const &_string
)
{
	string_ = _string;
}

void
sge::font::draw::detail::static_text_impl::rect(
	sge::font::rect const &_rect
)
{
	rect_ = _rect;

	sprite_.pos(
		_rect.pos()
	);

	sprite_.size(
		_rect.size()
	);
}

void
sge::font::draw::detail::static_text_impl::color(
	sge::image::color::any::object const &_color
)
{
	sprite_.color(
		sge::image::color::any::convert<
			sge::font::draw::detail::static_text_impl::color_format
		>(
			_color
		)
	);
}

void
sge::font::draw::detail::static_text_impl::rebuild_texture()
{
	texture_.take(
		renderer_.create_planar_texture(
			sge::renderer::texture::planar_parameters(
				fcppt::math::dim::structure_cast<
					sge::renderer::dim2
				>(
					rect_.size()
				),
				sge::image::color::format::a8,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null(),
				sge::renderer::texture::capabilities_field::null()
			)
		)
	);

	texture_part_.take(
		fcppt::make_unique_ptr<
			sge::texture::part_raw_ref
		>(
			fcppt::ref(
				*texture_
			)
		)
	);

	text_.take(
		font_.create_text(
			string_,
			text_parameters_
		)
	);

	{
		sge::renderer::texture::scoped_planar_lock const lock(
			*texture_,
			sge::renderer::lock_mode::writeonly
		);

		text_->render(
			lock.value()
		);
	}

	sprite_.texture(
		sge::texture::const_optional_part_ref(
			*texture_part_
		)
	);

	sprite_range_ =
		sge::sprite::geometry::update_one(
			sprite_,
			sprite_buffers_
		);
}
