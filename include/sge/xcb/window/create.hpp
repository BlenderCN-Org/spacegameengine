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


#ifndef SGE_XCB_WINDOW_CREATE_HPP_INCLUDED
#define SGE_XCB_WINDOW_CREATE_HPP_INCLUDED

#include <sge/xcb/window/auto_ptr.hpp>
#include <sge/xcb/window/id_num.hpp>
#include <sge/xcb/window/pos.hpp>
#include <sge/xcb/window/dim.hpp>
#include <sge/xcb/window/depth.hpp>
#include <sge/xcb/window/border_width.hpp>
#include <sge/xcb/window/class.hpp>
#include <sge/xcb/window/attribute/list_fwd.hpp>
#include <sge/xcb/visual/id_num.hpp>
#include <sge/xcb/connection_fwd.hpp>
#include <sge/xcb/symbol.hpp>

namespace sge
{
namespace xcb
{
namespace window
{

SGE_XCB_SYMBOL
auto_ptr
create(
	connection const &,
	id_num const &parent,
	pos const &,
	dim const &,
	depth const &,
	border_width const &,
	class_::type,
	visual::id_num const &,
	attribute::list const &
);

}
}
}

#endif
