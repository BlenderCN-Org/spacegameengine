/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/font/vector.hpp>
#include <sge/src/font/bitmap/char_metric_fwd.hpp>
#include <sge/src/font/bitmap/position.hpp>


sge::font::bitmap::position::position(
	sge::font::vector const _pos,
	sge::font::bitmap::char_metric const &_metric
)
:
	pos_{
		_pos
	},
	metric_{
		_metric
	}
{
}

sge::font::vector
sge::font::bitmap::position::pos() const
{
	return
		pos_;
}

sge::font::bitmap::char_metric const &
sge::font::bitmap::position::metric() const
{
	return
		metric_.get();
}
