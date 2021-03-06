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


#include <sge/systems/impl/window/original_system.hpp>
#include <sge/systems/impl/window/system_base.hpp>
#include <sge/window/system.hpp>
#include <awl/system/create.hpp>
#include <awl/system/object.hpp>
#include <awl/system/event/processor.hpp>
#include <fcppt/log/context_fwd.hpp>


sge::systems::impl::window::original_system::original_system(
	fcppt::log::context &_log_context
)
:
	sge::systems::impl::window::system_base(),
	awl_system_{
		awl::system::create(
			_log_context
		)
	},
	system_{
		*awl_system_
	}
{
}

sge::systems::impl::window::original_system::~original_system()
{
}

sge::window::system &
sge::systems::impl::window::original_system::get()
{
	return
		system_;
}
