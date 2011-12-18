/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_SYSTEMS_MODULES_INPUT_CURSOR_MODIFIER_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_INPUT_CURSOR_MODIFIER_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/cursor/discover_event_fwd.hpp>
#include <sge/src/systems/modules/input/cursor_modifier_fwd.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/bitfield/basic_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace systems
{
namespace modules
{
namespace input
{

class cursor_modifier
{
	FCPPT_NONCOPYABLE(
		cursor_modifier
	);
public:
	cursor_modifier(
		sge::input::processor &,
		systems::cursor_option_field const &
	);

	~cursor_modifier();
private:
	void
	cursor_discover(
		sge::input::cursor::discover_event const &
	);

	systems::cursor_option_field const options_;

	fcppt::signal::scoped_connection const connection_;
};

}
}
}
}

#endif
