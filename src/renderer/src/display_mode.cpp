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


#include "../display_mode.hpp"
	
sge::display_mode::display_mode(const screen_unit width,
                                const screen_unit height,
                                const bit_depth::type depth,
                                const unsigned refresh_rate)
 : size(width, height),
   depth(depth),
   refresh_rate(refresh_rate)
{}

sge::screen_unit sge::display_mode::width() const
{
	return size.w();
}

sge::screen_unit sge::display_mode::height() const
{
	return size.h();
}

bool sge::operator== (const display_mode& l, const display_mode& r)
{
	return l.depth == r.depth && l.size == r.size && l.refresh_rate == r.refresh_rate;
}

bool sge::operator!= (const display_mode& l, const display_mode& r)
{
	return !(l==r);
}
