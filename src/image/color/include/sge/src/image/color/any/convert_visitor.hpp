/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_IMAGE_COLOR_ANY_CONVERT_VISITOR_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_ANY_CONVERT_VISITOR_HPP_INCLUDED

#include <sge/image/mizuiro_color.hpp>
#include <sge/src/image/color/converter.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace any
{

template<
	typename Dest
>
class convert_visitor
{
public:
	typedef typename sge::image::mizuiro_color<
		Dest
	>::type result_type;

	template<
		typename Source
	>
	result_type const
	operator()(
		Source const &_source
	) const
	{
		return
			sge::image::color::converter::execute<
				Dest
			>(
				_source
			);
	}
};

}
}
}
}

#endif
