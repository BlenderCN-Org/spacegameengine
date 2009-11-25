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


#ifndef SGE_OPENGL_XRANDR_MODE_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_MODE_HPP_INCLUDED

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <sge/renderer/refresh_rate.hpp>

namespace sge
{
namespace opengl
{
namespace xrandr
{

class mode {
public:
	mode(
		int index,
		Rotation,
		renderer::refresh_rate
	);

	int
	index() const;

	Rotation
	rotation() const;

	renderer::refresh_rate
	rate() const;
private:
	int const index_;
	Rotation const rotation_;
	renderer::refresh_rate const rate_;
};

}
}
}

#endif
