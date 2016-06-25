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
#include <sge/gui/duration.hpp>
#include <sge/gui/focus_change.hpp>
#include <sge/gui/get_focus.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/optional_focus.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <sge/input/key/code.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe_void.hpp>


sge::gui::widget::base::base()
:
	parent_(),
	enabled_{
		true
	}
{
}

sge::gui::widget::base::~base()
{
	fcppt::optional::maybe_void(
		parent_,
		[
			this
		](
			fcppt::reference<
				sge::gui::widget::base
			> const _parent
		)
		{
			_parent.get().unregister(
				*this
			);
		}
	);
}

void
sge::gui::widget::base::on_update(
	sge::gui::duration
)
{
}

sge::gui::get_focus
sge::gui::widget::base::on_click(
	sge::rucksack::vector
)
{
	return
		sge::gui::get_focus(
			false
		);
}

void
sge::gui::widget::base::on_key(
	sge::input::key::code
)
{
}

void
sge::gui::widget::base::on_char(
	sge::font::char_type
)
{
}

void
sge::gui::widget::base::on_focus_changed(
	sge::gui::focus_change
)
{
}

sge::gui::widget::optional_ref
sge::gui::widget::base::on_tab(
	sge::gui::widget::optional_focus &
)
{
	return
		sge::gui::widget::optional_ref();
}

void
sge::gui::widget::base::parent(
	sge::gui::widget::optional_ref const _new_parent
)
{
	if(
		parent_.has_value()
	)
		this->layout().parent(
			sge::rucksack::widget::optional_ref()
		);

	parent_ =
		_new_parent;

	fcppt::optional::maybe_void(
		_new_parent,
		[
			this
		](
			fcppt::reference<
				sge::gui::widget::base
			> const _parent
		)
		{
			this->layout().parent(
				sge::rucksack::widget::optional_ref(
					fcppt::make_ref(
						_parent.get().layout()
					)
				)
			);
		}
	);
}

void
sge::gui::widget::base::enable(
	bool const _enabled
)
{
	enabled_ =
		_enabled;
}

bool
sge::gui::widget::base::enabled() const
{
	return
		enabled_;
}

void
sge::gui::widget::base::unregister(
	sge::gui::widget::base const &
)
{
}
