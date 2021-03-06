/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/font/char_type.hpp>
#include <sge/gui/focus_change.hpp>
#include <sge/gui/get_focus.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/frame.hpp>
#include <sge/gui/widget/optional_focus.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <sge/input/key/code.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>


sge::gui::widget::frame::frame(
	sge::gui::style::base const &_style,
	sge::gui::widget::base &_child
)
:
	sge::gui::widget::base(),
	style_(
		_style
	),
	child_(
		_child
	),
	layout_{
		_child.layout(),
		_style.frame_padding()
	}
{
	child_.parent(
		sge::gui::widget::optional_ref(
			fcppt::reference_to_base<
				sge::gui::widget::base
			>(
				fcppt::make_ref(
					*this
				)
			)
		)
	);
}

sge::gui::widget::frame::~frame()
{
}

sge::rucksack::widget::base &
sge::gui::widget::frame::layout()
{
	return
		layout_;
}

void
sge::gui::widget::frame::on_draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context
)
{
	style_.draw_frame(
		_renderer,
		_context,
		this->layout().area(),
		layout_.padding()
	);

	child_.on_draw(
		_renderer,
		_context
	);
}

sge::gui::get_focus
sge::gui::widget::frame::on_click(
	sge::rucksack::vector const _pos
)
{
	return
		child_.on_click(
			_pos
		);
}

void
sge::gui::widget::frame::on_key(
	sge::input::key::code const _key
)
{
	return
		child_.on_key(
			_key
		);
}

void
sge::gui::widget::frame::on_char(
	sge::font::char_type const _char
)
{
	child_.on_char(
		_char
	);
}

void
sge::gui::widget::frame::on_focus_changed(
	sge::gui::focus_change const _change
)
{
	child_.on_focus_changed(
		_change
	);
}

sge::gui::widget::optional_ref
sge::gui::widget::frame::on_tab(
	sge::gui::widget::optional_focus &_focus
)
{
	return
		child_.on_tab(
			_focus
		);
}
