/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_IMAGE2D_ALGORITHM_CONVERT_CONDITIONAL_HPP_INCLUDED
#define SGE_IMAGE2D_ALGORITHM_CONVERT_CONDITIONAL_HPP_INCLUDED

#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image/algorithm/accepted_format_array.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace image2d
{
namespace algorithm
{

SGE_SYMBOL void
convert_conditional(
	image::raw_pointer,
	image2d::dim const &,
	image::color::format::type,
	image2d::pitch const &, 
	image::algorithm::accepted_format_array const &
);

}
}
}

#endif
