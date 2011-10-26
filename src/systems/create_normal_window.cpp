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


#include <sge/src/systems/create_normal_window.hpp>
#include <sge/systems/window.hpp>
#include <sge/window/create.hpp>
#include <sge/window/create_simple_from_awl.hpp>
#include <sge/window/instance_ptr.hpp>
#include <sge/window/parameters.hpp>
#include <awl/system/object_shared_ptr.hpp>


sge::window::instance_ptr const
sge::systems::create_normal_window(
	awl::system::object_shared_ptr const _system,
	sge::systems::window const &_window_param
)
{
	return
		sge::window::create(
			sge::window::parameters(
				_system,
				sge::window::create_simple_from_awl(
					*_system,
					_window_param.parameter().get<
						sge::window::simple_parameters
					>()
				)
			)
			.window_event_processor(
				_window_param.window_event_processor()
			)
			.io_service(
				_window_param.io_service()
			)
		);
}
