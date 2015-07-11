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


#ifndef SGE_GUI_WIDGET_BUTTON_HPP_INCLUDED
#define SGE_GUI_WIDGET_BUTTON_HPP_INCLUDED

#include <sge/gui/click_callback.hpp>
#include <sge/gui/click_function.hpp>
#include <sge/gui/get_focus_fwd.hpp>
#include <sge/gui/optional_needed_width_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/button_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class button
:
	public sge::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		button
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	button(
		sge::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::font::string const &,
		sge::gui::optional_needed_width
	);

	SGE_GUI_DETAIL_SYMBOL
	~button()
	override;

	SGE_GUI_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	click(
		sge::gui::click_callback const &
	);

	SGE_GUI_DETAIL_SYMBOL
	sge::font::string const &
	text() const;

	SGE_GUI_DETAIL_SYMBOL
	void
	text(
		sge::font::string const &
	);

	SGE_GUI_DETAIL_SYMBOL
	sge::rucksack::widget::base &
	layout()
	override;
private:
	void
	on_draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &
	)
	override;

	sge::gui::get_focus const
	on_click(
		sge::rucksack::vector
	)
	override;

	sge::font::draw::static_text
	make_static_text(
		sge::font::string const &
	);

	sge::gui::style::base const &style_;

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sge::font::string text_;

	sge::font::draw::static_text static_text_;

	sge::rucksack::widget::dummy layout_;

	typedef
	fcppt::signal::object<
		sge::gui::click_function
	>
	click_signal;

	click_signal click_;
};

}
}
}

#endif
