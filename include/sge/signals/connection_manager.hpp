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


#ifndef SGE_SIGNALS_CONNECTION_MANAGER_HPP_INCLUDED
#define SGE_SIGNALS_CONNECTION_MANAGER_HPP_INCLUDED

#include "connection.hpp"
#include "../export.hpp"
#include <boost/noncopyable.hpp>
#include <vector>

namespace sge
{
namespace signals
{

// TODO: we should use boost::signals::trackable instead
class connection_manager : boost::noncopyable {
public:
	SGE_SYMBOL ~connection_manager();

	SGE_SYMBOL void connect(
		connection const &);
private:
	typedef std::vector<
		connection
	> connection_vector;

	connection_vector connections;
};

}
}

#endif
