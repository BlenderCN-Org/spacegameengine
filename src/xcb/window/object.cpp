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


#include <sge/xcb/window/object.hpp>
#include <sge/xcb/connection.hpp>
#include <xcb/xcb.h>

sge::xcb::window::object::object(
	id_num const &id_,
	xcb::connection const &connection_
)
:
	id_(id_),
	connection_(connection_)
{}

sge::xcb::window::object::~object()
{
	xcb_destroy_window(
		connection_.get(),
		id_
	);
}

sge::xcb::connection const &
sge::xcb::window::object::connection() const
{
	return connection_;
}

SGE_XCB_SYMBOL
sge::xcb::window::id_num const
sge::xcb::window::object::id() const
{
	return id_;
}
