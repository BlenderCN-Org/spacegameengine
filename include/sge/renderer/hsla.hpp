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


#ifndef SGE_RENDERER_HSLA_HPP_INCLUDED
#define SGE_RENDERER_HSLA_HPP_INCLUDED

#include "color.hpp"

namespace sge
{
namespace renderer
{

// TODO: rewrite this to use GIL
class hsla {
public:
	static const color_element hsl_max = 240;
	static const color_element rgb_max = color_element_max;
	static const color_element hue_undefined = hsl_max * 2 / 3;

	explicit hsla(color c);
	hsla(color_element h, color_element s, color_element l, color_element a);
	color to_color() const;

	void hue(color_element);
	void lum(color_element);
	void sat(color_element);
	void a(color_element);

	color_element hue() const;
	color_element lum() const;
	color_element sat() const;
	color_element a() const;
private:
	void init(color_element r, color_element g, color_element b);
	color_element hue_,
	              sat_,
	              lum_,
	              a_;
};

}
}

#endif
