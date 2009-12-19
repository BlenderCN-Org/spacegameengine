/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_FREETYPE_CHAR_METRIC_HPP_INCLUDED
#define SGE_FREETYPE_CHAR_METRIC_HPP_INCLUDED

#include <sge/font/pos.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/char_metric.hpp>
#include <sge/font/image_view.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <sge/image/alpha8.hpp>
#include <sge/image/store.hpp>
#include <sge/char_type.hpp>

namespace sge
{
namespace freetype
{

class face;

class char_metric : public font::char_metric {
public:
	char_metric(
		face &,
		char_type
	);

	~char_metric();

	font::const_image_view const pixmap() const;
	font::pos const offset() const;
	font::unit x_advance() const;
private:
	typedef sge::image::alpha8 buffer_type;
	buffer_type buffer_;
	font::pos   offset_;
	font::unit  x_advance_;
};

}
}

#endif
