/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <stdexcept>
#include "../x_color.hpp"
	
sge::xinput::x_color::x_color(Display* const dsp, Colormap colormap)
 : dsp(dsp),
   colormap(colormap)
{
	XColor dummy;
	if(XAllocNamedColor(dsp, colormap, "black", &_color, &dummy ) == 0)
		throw std::runtime_error("XAllocNamedColor() failed");
}

sge::xinput::x_color::~x_color()
{
	XFreeColors(dsp, colormap, &_color.pixel, 1, 0);
}

XColor sge::xinput::x_color::color() const
{
	return _color;
}
