/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SCOPED_CONNECTION_HPP_INCLUDED
#define SGE_SCOPED_CONNECTION_HPP_INCLUDED

#include "callback_connection.hpp"
#include "export.hpp"
#include <boost/signals/connection.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{

typedef boost::signals::scoped_connection scoped_connection;

class SGE_CLASS_SYMBOL scoped_connection_manager : boost::noncopyable {
public:
	typedef unsigned key_type;

	key_type scoped_connect(sge::callback_connection);
	void scoped_disconnect(key_type);

private:
	unsigned anonymous_connections;
	boost::ptr_map<key_type, scoped_connection> cons;
};

}

#endif
