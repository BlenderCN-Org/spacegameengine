/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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


#ifndef SGE_GUI_BUTTON_HPP_INCLUDED
#define SGE_GUI_BUTTON_HPP_INCLUDED

#include "widget.hpp"

namespace sge {
namespace gui {

class button : public widget {
public:
	button(widget *parent, color bg, std::string name="");

protected:
	color bg;
	void on_paint(const events::paint_event &);
};

}
}

#endif // SGE_GUI_BUTTON_HPP_INCLUDED
