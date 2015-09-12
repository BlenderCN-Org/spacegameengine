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


#include <sge/font/dim.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/draw/set_matrices.hpp>
#include <sge/font/draw/set_states.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/src/font/draw/detail/static_text_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::font::draw::static_text::static_text(
	sge::renderer::device::ffp &_device,
	sge::font::object &_font,
	sge::font::string const &_string,
	sge::font::text_parameters const &_parameters,
	sge::font::vector const &_pos,
	sge::image::color::any::object const &_color,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
:
	impl_(
		fcppt::make_unique_ptr<
			sge::font::draw::detail::static_text_impl
		>(
			_device,
			_font,
			_string,
			_parameters,
			_pos,
			_color,
			_emulate_srgb
		)
	)
{
}

sge::font::draw::static_text::static_text(
	static_text &&
) = default;

sge::font::draw::static_text &
sge::font::draw::static_text::operator=(
	static_text &&
) = default;

sge::font::draw::static_text::~static_text()
{
}

void
sge::font::draw::static_text::draw(
	sge::renderer::context::ffp &_context
) const
{
	this->draw_advanced(
		_context,
		sge::font::draw::set_matrices(
			true
		),
		sge::font::draw::set_states(
			true
		)
	);
}

void
sge::font::draw::static_text::draw_advanced(
	sge::renderer::context::ffp &_context,
	sge::font::draw::set_matrices const &_set_matrices,
	sge::font::draw::set_states const &_set_states
) const
{
	impl_->draw(
		_context,
		_set_matrices,
		_set_states
	);
}

void
sge::font::draw::static_text::pos(
	sge::font::vector const &_pos
)
{
	impl_->pos(
		_pos
	);
}

void
sge::font::draw::static_text::color(
	sge::image::color::any::object const &_color
)
{
	impl_->color(
		_color
	);
}


sge::font::vector const
sge::font::draw::static_text::pos() const
{
	return
		impl_->pos();
}

sge::font::rect const
sge::font::draw::static_text::rect() const
{
	return
		impl_->rect();
}

sge::font::dim const
sge::font::draw::static_text::logical_size() const
{
	return
		impl_->logical_size();
}

sge::font::text const &
sge::font::draw::static_text::text() const
{
	return
		impl_->text();
}
