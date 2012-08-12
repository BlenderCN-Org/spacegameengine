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


#ifndef SGE_SRC_FONT_BITMAP_CHAR_METRIC_HPP_INCLUDED
#define SGE_SRC_FONT_BITMAP_CHAR_METRIC_HPP_INCLUDED

#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/src/font/bitmap/const_view.hpp>
#include <sge/src/font/bitmap/char_metric_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace font
{
namespace bitmap
{

class char_metric
{
	FCPPT_NONCOPYABLE(
		char_metric
	);
public:
	char_metric(
		sge::font::bitmap::const_view const &,
		sge::font::vector const &offset,
		sge::font::unit x_advance
	);

	~char_metric();

	sge::font::bitmap::const_view const
	pixmap() const;

	sge::font::vector const
	offset() const;

	sge::font::unit
	x_advance() const;
private:
	sge::font::bitmap::const_view const pixmap_;

	sge::font::vector const offset_;

	sge::font::unit const x_advance_;
};

}
}
}

#endif
