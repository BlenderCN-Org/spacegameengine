/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_FONT_TEXT_DRAW_HPP_INCLUDED
#define SGE_FONT_TEXT_DRAW_HPP_INCLUDED

#include <sge/font/metrics_fwd.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/text/align_h.hpp>
#include <sge/font/text/align_v.hpp>
#include <sge/font/text/drawer_fwd.hpp>
#include <sge/font/text/flags_field.hpp>
#include <sge/font/text/part_fwd.hpp>
#include <sge/font/text/string.hpp>
#include <sge/font/text/symbol.hpp>
#include <sge/renderer/context/object_fwd.hpp>


namespace sge
{
namespace font
{
namespace text
{

SGE_FONT_TEXT_SYMBOL
text::part const
draw(
	sge::renderer::context::object &,
	font::metrics &,
	text::drawer &,
	font::text::string const &,
	font::rect const &,
	text::align_h::type,
	text::align_v::type,
	text::flags_field const &
);

}
}
}

#endif
