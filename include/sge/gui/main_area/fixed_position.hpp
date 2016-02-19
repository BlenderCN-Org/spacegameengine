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


#ifndef SGE_GUI_MAIN_AREA_FIXED_POSITION_HPP_INCLUDED
#define SGE_GUI_MAIN_AREA_FIXED_POSITION_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/minimum_size.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace main_area
{

class fixed_position
:
	public sge::gui::main_area::base
{
	FCPPT_NONCOPYABLE(
		fixed_position
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	fixed_position(
		sge::gui::widget::base &,
		sge::rucksack::vector
	);

	SGE_GUI_DETAIL_SYMBOL
	~fixed_position()
	override;

	SGE_GUI_DETAIL_SYMBOL
	void
	relayout()
	override;
private:
	sge::gui::widget::base &
	widget()
	override;

	sge::gui::widget::base &widget_;

	sge::gui::widget::minimum_size minimum_size_;
};

}
}
}

#endif
