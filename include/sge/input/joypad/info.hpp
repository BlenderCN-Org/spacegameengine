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


#ifndef SGE_INPUT_JOYPAD_INFO_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_INFO_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/info/unique_id.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/info_fwd.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>


namespace sge
{
namespace input
{
namespace joypad
{

class info
{
public:
	SGE_INPUT_DETAIL_SYMBOL
	info(
		sge::input::joypad::absolute_axis_info_container const &,
		sge::input::joypad::button_info_container const &,
		sge::input::joypad::relative_axis_info_container const &,
		sge::input::info::name const &,
		sge::input::info::unique_id const &
	);

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::absolute_axis_info_container const &
	absolute_axes() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::button_info_container const &
	buttons() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::relative_axis_info_container const &
	relative_axes() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::info::name const &
	name() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::info::unique_id const &
	unique_id() const;
private:
	sge::input::joypad::absolute_axis_info_container absolute_axes_;

	sge::input::joypad::button_info_container buttons_;

	sge::input::joypad::relative_axis_info_container relative_axes_;

	sge::input::info::name name_;

	sge::input::info::unique_id unique_id_;
};

}
}
}

#endif
