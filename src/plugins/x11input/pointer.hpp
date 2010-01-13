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


#ifndef SGE_X11INPUT_POINTER_HPP_INCLUDED
#define SGE_X11INPUT_POINTER_HPP_INCLUDED

#include "mouse_coordinate.hpp"
#include <sge/x11/window_ptr.hpp>

namespace sge
{
namespace x11input
{

mouse_pos const
get_pointer(
	x11::window_ptr);

void warp_pointer(
	x11::window_ptr wnd,
	mouse_pos const &);

}
}

#endif
