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


#ifndef SGE_XINPUT_X_PIXMAP_HPP_INCLUDED
#define SGE_XINPUT_X_PIXMAP_HPP_INCLUDED

#include <X11/Xlib.h>
#include <sge/x_display.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace xinput
{

class x_pixmap : boost::noncopyable {
public:
	x_pixmap(x_display_ptr, Window wnd);
	~x_pixmap();
	Pixmap pixmap() const;
private:
	x_display_ptr dsp;
	Pixmap _pixmap;
};

}
}

#endif
