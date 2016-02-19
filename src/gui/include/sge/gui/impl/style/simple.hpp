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


#ifndef SGE_GUI_IMPL_STYLE_SIMPLE_HPP_INCLUDED
#define SGE_GUI_IMPL_STYLE_SIMPLE_HPP_INCLUDED

#include <sge/gui/fill_color_fwd.hpp>
#include <sge/gui/fill_level_fwd.hpp>
#include <sge/gui/text_color_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/padding_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace impl
{
namespace style
{

class simple
:
	public sge::gui::style::base
{
	FCPPT_NONCOPYABLE(
		simple
	);
public:
	simple();

	~simple()
	override;
private:
	sge::rucksack::dim
	button_spacing() const
	override;

	void
	draw_button(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	void
	draw_bar(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::rucksack::axis,
		sge::gui::fill_level,
		sge::gui::fill_color const &
	) const
	override;

	sge::rucksack::padding
	frame_padding() const
	override;

	void
	draw_frame(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::rucksack::padding
	) const
	override;

	sge::rucksack::dim
	edit_spacing() const
	override;

	void
	draw_edit(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	sge::rucksack::dim
	image_spacing() const
	override;

	void
	draw_image(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	sge::rucksack::dim
	text_spacing() const
	override;

	void
	draw_text(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	sge::gui::text_color
	text_color() const
	override;

	sge::rucksack::dim
	spacing() const;
};

}
}
}
}

#endif
