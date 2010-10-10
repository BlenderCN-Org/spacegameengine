/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_INPUT_KEYBOARD_DEVICE_HPP_INCLUDED
#define SGE_INPUT_KEYBOARD_DEVICE_HPP_INCLUDED

#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_repeat_callback.hpp>
#include <sge/input/device.hpp>
#include <sge/class_symbol.hpp>
#include <sge/symbol.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace input
{
namespace keyboard
{

class SGE_CLASS_SYMBOL device
:
	public input::device
{
	FCPPT_NONCOPYABLE(
		device
	)
protected:
	SGE_SYMBOL device();
public:
	SGE_SYMBOL virtual ~device();

	virtual fcppt::signal::auto_connection
	register_key_callback(
		key_callback const &		
	) = 0;

	virtual fcppt::signal::auto_connection
	register_key_repeat_callback(
		key_repeat_callback const &
	) = 0;
};

}
}
}

#endif
