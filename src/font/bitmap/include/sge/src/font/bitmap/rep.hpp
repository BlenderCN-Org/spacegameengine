/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_FONT_BITMAP_REP_HPP_INCLUDED
#define SGE_SRC_FONT_BITMAP_REP_HPP_INCLUDED

#include <sge/font/rect.hpp>
#include <sge/src/font/bitmap/line_vector.hpp>
#include <sge/src/font/bitmap/rep_fwd.hpp>


namespace sge
{
namespace font
{
namespace bitmap
{

class rep
{
public:
	rep(
		sge::font::bitmap::line_vector &&,
		sge::font::rect const &
	);

	sge::font::bitmap::line_vector const &
	lines() const;

	sge::font::rect
	rect() const;
private:
	sge::font::bitmap::line_vector lines_;

	sge::font::rect rect_;
};

}
}
}

#endif
