/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_XCB_WINDOW_OBJECT_HPP_INCLUDED
#define SGE_XCB_WINDOW_OBJECT_HPP_INCLUDED

#include <sge/xcb/window/object_fwd.hpp>
#include <sge/xcb/window/id_num.hpp>
#include <sge/xcb/connection_fwd.hpp>
#include <sge/xcb/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace xcb
{
namespace window
{

class object
{
	FCPPT_NONCOPYABLE(object)
public:
	SGE_XCB_SYMBOL
	explicit object(
		id_num const &,
		connection const &
	);

	SGE_XCB_SYMBOL
	~object();

	SGE_XCB_SYMBOL
	void
	map();
private:
	id_num const id_;

	connection const &connection_;
};

}
}
}

#endif
