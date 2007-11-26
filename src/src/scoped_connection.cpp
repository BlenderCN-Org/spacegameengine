/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (slashlife@slashlife.org)

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

#include <sstream>

#include "../scoped_connection.hpp"

void sge::scoped_connection_manager::scoped_connect(key_type k, sge::callback_connection v) {
	scoped_disconnect(k);
	cons.insert(k, new sge::scoped_connection(v));
}

sge::scoped_connection_manager::key_type sge::scoped_connection_manager::scoped_connect(sge::callback_connection v) {
	key_type k;
	{ std::stringstream ss;
		ss << char(0) << anonymous_connections++;
		k = ss.str();
	}
	scoped_connect(k, v);
	return k;
}

void sge::scoped_connection_manager::scoped_disconnect(const key_type &k) {
	cons.erase(k);
}

