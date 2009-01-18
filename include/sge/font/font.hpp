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


#ifndef SGE_FONT_FONT_HPP_INCLUDED
#define SGE_FONT_FONT_HPP_INCLUDED

#include "pos.hpp"
#include "dim.hpp"
#include "unit.hpp"
#include "drawer_fwd.hpp"
#include "metrics_fwd.hpp"
#include "../string.hpp"
#include "../export.hpp"
#include "../renderer/size_type.hpp"

namespace sge
{
namespace font
{

namespace align_h
{
	enum type {
		left,
		right,
		center
	};
}

namespace align_v
{
	enum type {
		top,
		bottom,
		center
	};
}

namespace flags
{
	enum type {
		none           = 0,
		no_multi_line  = 1 << 0,
		no_line_wrap   = 1 << 1,
		default_       = none
	};
}
typedef unsigned flag_t;

class text_size_t;

class SGE_CLASS_SYMBOL font {
public:
	typedef renderer::size_type size_type;

	SGE_SYMBOL explicit font(
		metrics_ptr metrics,
		drawer_ptr drawer = drawer_ptr());
	SGE_SYMBOL ~font();

	SGE_SYMBOL unit height() const;

	SGE_SYMBOL text_size_t const
	draw_text(
		string const &text,
		pos start_pos,
		dim max_size,
		align_h::type = align_h::left,
		align_v::type = align_v::top,
		flag_t flags = flags::default_) const;

	SGE_SYMBOL text_size_t const
	line_width(
		string::const_iterator beg,
		string::const_iterator end,
		unit width,
		flag_t tflags) const;

	SGE_SYMBOL text_size_t const
	text_size(
		string::const_iterator beg,
		string::const_iterator end,
		dim max_size,
		flag_t flags = flags::default_) const;

	SGE_SYMBOL text_size_t const
	text_size(
		string const &s, 
		dim max_size,
		flag_t flags = flags::default_) const;

	SGE_SYMBOL unit char_space(char_type ch) const;

	SGE_SYMBOL metrics_ptr const metrics() const;
	SGE_SYMBOL drawer_ptr const drawer() const;
private:
	metrics_ptr       metrics_;
	drawer_ptr        drawer_;
};

}
}

#endif
