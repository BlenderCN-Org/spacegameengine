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


#ifndef SGE_SRC_FONT_TEXT_ALIGN_POS_H_HPP_INCLUDED
#define SGE_SRC_FONT_TEXT_ALIGN_POS_H_HPP_INCLUDED

#include <sge/font/dim.hpp>
#include <sge/font/pos.hpp>
#include <sge/font/text/align_h.hpp>
#include <sge/font/text/part.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>


namespace sge
{
namespace font
{
namespace text
{

inline
void
align_pos_h(
	font::pos &_pos,
	font::dim const &_max_sz,
	text::part const &_line_size,
	text::align_h::type const _align_h
)
{
	switch(
		_align_h
	)
	{
	case align_h::center:
		_pos.x() += (_max_sz.w() - _line_size.size().w()) / 2;
		return;
	case align_h::right:
		_pos.x() += _max_sz.w() - _line_size.size().w();
		return;
	case align_h::left:
		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

}
}
}

#endif
