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


#ifndef SGE_INPUT_CURSOR_RELATIVE_MOVEMENT_HPP_INCLUDED
#define SGE_INPUT_CURSOR_RELATIVE_MOVEMENT_HPP_INCLUDED

#include <sge/input/cursor/relative_movement_fwd.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/move_function.hpp>
#include <sge/input/cursor/object_ptr.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/symbol.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace input
{
namespace cursor
{

class relative_movement
{
	FCPPT_NONCOPYABLE(
		relative_movement
	)
public:
	SGE_SYMBOL
	explicit relative_movement(
		cursor::object_ptr
	);

	SGE_SYMBOL
	~relative_movement();

	SGE_SYMBOL
	fcppt::signal::auto_connection
	move_callback(
		cursor::move_callback const &
	);
private:
	void
	move_callback_internal(
		cursor::move_event const &
	);

	typedef fcppt::signal::object<
		cursor::move_function
	> move_signal;

	cursor::object_ptr const cursor_;

	cursor::position last_position_;

	move_signal move_signal_;

	fcppt::signal::scoped_connection const connection_;
};

}
}
}

#endif
