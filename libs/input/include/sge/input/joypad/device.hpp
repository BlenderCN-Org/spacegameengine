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


#ifndef SGE_INPUT_JOYPAD_DEVICE_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_DEVICE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/absolute_axis_callback.hpp>
#include <sge/input/joypad/button_callback.hpp>
#include <sge/input/joypad/device_fwd.hpp>
#include <sge/input/joypad/info_fwd.hpp>
#include <sge/input/joypad/relative_axis_callback.hpp>
#include <sge/input/joypad/ff/effect_unique_ptr.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>


namespace sge
{
namespace input
{
namespace joypad
{

class SGE_CORE_DETAIL_CLASS_SYMBOL device
{
	FCPPT_NONCOPYABLE(
		device
	);
protected:
	SGE_INPUT_DETAIL_SYMBOL
	device();
public:
	SGE_INPUT_DETAIL_SYMBOL
	virtual
	~device() = 0;

	virtual
	fcppt::signal::auto_connection
	absolute_axis_callback(
		sge::input::joypad::absolute_axis_callback const &
	) = 0;

	virtual
	fcppt::signal::auto_connection
	button_callback(
		sge::input::joypad::button_callback const &
	) = 0;

	virtual
	fcppt::signal::auto_connection
	relative_axis_callback(
		sge::input::joypad::relative_axis_callback const &
	) = 0;

	virtual
	sge::input::joypad::info const &
	info() const = 0;

	virtual
	sge::input::joypad::ff::effect_unique_ptr
	create_ff_effect(
		sge::input::joypad::ff::parameters const &
	) = 0;
};

}
}
}

#endif
