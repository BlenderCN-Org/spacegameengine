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


#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/dummy.hpp>
#include <sge/gui/widget/preferred_size.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>


sge::gui::widget::preferred_size::preferred_size(
	sge::rucksack::dim const &_area
)
:
	sge::gui::widget::dummy(),
	layout_{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					_area.w()
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					_area.h()
				}
			}
		}
	}
{
}

sge::gui::widget::preferred_size::~preferred_size()
{
}

sge::rucksack::widget::base &
sge::gui::widget::preferred_size::layout()
{
	return
		layout_;
}
