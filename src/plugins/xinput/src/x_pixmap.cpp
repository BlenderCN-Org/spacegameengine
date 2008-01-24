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


#include "../../../exception.hpp"
#include "../x_pixmap.hpp"

const char bm_no_data[] = { 0,0,0,0, 0,0,0,0 };

sge::xinput::x_pixmap::x_pixmap(const x_display_ptr dsp, const Window wnd)
 : dsp(dsp),
   _pixmap(XCreateBitmapFromData(dsp->get(), wnd, bm_no_data, 8, 8))
{
	if(pixmap() == None)
		throw exception(SGE_TEXT("XCreateBitmapFromData() failed!"));
}

sge::xinput::x_pixmap::~x_pixmap()
{
	XFreePixmap(dsp->get(), pixmap());
}

Pixmap sge::xinput::x_pixmap::pixmap() const
{
	return _pixmap;
}
