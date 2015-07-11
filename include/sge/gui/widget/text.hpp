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


#ifndef SGE_GUI_WIDGET_TEXT_HPP_INCLUDED
#define SGE_GUI_WIDGET_TEXT_HPP_INCLUDED

#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/text_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/axis_policy_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class text
:
	public sge::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		text
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	text(
		sge::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::font::string const &,
		sge::gui::text_color const &,
		sge::gui::optional_needed_width
	);

	SGE_GUI_DETAIL_SYMBOL
	~text()
	override;

	SGE_GUI_DETAIL_SYMBOL
	void
	value(
		sge::font::string const &
	);

	SGE_GUI_DETAIL_SYMBOL
	void
	text_color(
		sge::gui::text_color const &
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

	sge::rucksack::axis_policy
	horizontal_policy() const;

	sge::gui::style::base const &style_;

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sge::gui::text_color text_color_;

	sge::gui::optional_needed_width const needed_width_;

	sge::font::string value_;

	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif
