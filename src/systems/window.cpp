/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/systems/window.hpp>
#include <awl/mainloop/io_service_fwd.hpp>
#include <awl/mainloop/optional_io_service_ref.hpp>


sge::systems::window::window(
	sge::systems::window::parameter_variant const &_parameter
)
:
	parameter_(
		_parameter
	),
	io_service_(),
	show_(true)
{
}

sge::systems::window &
sge::systems::window::io_service(
	awl::mainloop::io_service &_io_service
)
{
	io_service_ =
		awl::mainloop::optional_io_service_ref(
			_io_service
		);

	return *this;
}

sge::systems::window &
sge::systems::window::dont_show()
{
	show_ = false;

	return *this;
}

sge::systems::window::parameter_variant const &
sge::systems::window::parameter() const
{
	return parameter_;
}

awl::mainloop::optional_io_service_ref const
sge::systems::window::io_service() const
{
	return io_service_;
}

bool
sge::systems::window::show() const
{
	return show_;
}
