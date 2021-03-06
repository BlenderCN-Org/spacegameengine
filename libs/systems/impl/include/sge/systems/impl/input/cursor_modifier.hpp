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


#ifndef SGE_SYSTEMS_IMPL_INPUT_CURSOR_MODIFIER_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_INPUT_CURSOR_MODIFIER_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/impl/input/cursor_modifier_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace systems
{
namespace impl
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
		sge::input::processor const &,
		sge::window::object &,
		sge::systems::cursor_option_field const &
	);

	~cursor_modifier();
private:
	awl::event::container
	on_event(
		awl::window::event::base const &
	) const;

	sge::systems::cursor_option_field const options_;

	fcppt::signal::auto_connection const connection_;
};

}
}
}
}

#endif
