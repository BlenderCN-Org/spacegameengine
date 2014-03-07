/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/src/systems/modules/window/system_base.hpp>
#include <sge/src/systems/modules/window/wrapped_system.hpp>
#include <sge/systems/wrapped_window.hpp>
#include <sge/window/system.hpp>


sge::systems::modules::window::wrapped_system::wrapped_system(
	sge::systems::wrapped_window const &_parameters
)
:
	sge::systems::modules::window::system_base(),
	system_(
		_parameters.awl_system(),
		_parameters.awl_system_event_processor(),
		_parameters.awl_event_processor()
	)
{
}

sge::systems::modules::window::wrapped_system::~wrapped_system()
{
}

sge::window::system &
sge::systems::modules::window::wrapped_system::get()
{
	return
		system_;
}
