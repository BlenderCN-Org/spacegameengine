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


#ifndef SGE_GUI_RECTANGLE_HPP_INCLUDED
#define SGE_GUI_RECTANGLE_HPP_INCLUDED

#include "types.hpp"
#include "element.hpp"
#include "../sprite/sprite.hpp"

namespace sge
{
namespace gui
{

class manager;

class rectangle : public element, private sprite {
public:
	rectangle(manager& m, element* parent, point pos, dim sz, const std::string& texture_name, bool visible = true, bool enabled = true);
	const unit& x() const;
	unit& x();
	const unit& y() const;
	unit& y();
	const point& pos() const;
	point& pos();

	using sprite::point;
	using sprite::dim;
	using sprite::width;
	using sprite::height;
	using sprite::size;
	using sprite::get_rect;
	using sprite::center;
	using sprite::repeat;
	bool intersects(point p) const;
protected:
	virtual void on_draw(const draw_event& event);
	using sprite::set_texture;
private:
	point relative_pos() const;
	point rel_pos;
};

}
}

#endif
