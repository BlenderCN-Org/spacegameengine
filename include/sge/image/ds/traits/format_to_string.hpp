/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_IMAGE_DS_TRAITS_FORMAT_TO_STRING_HPP_INCLUDED
#define SGE_IMAGE_DS_TRAITS_FORMAT_TO_STRING_HPP_INCLUDED

#include <sge/image/ds/format_fwd.hpp>
#include <sge/image/ds/symbol.hpp>
#include <sge/image/ds/tag.hpp>
#include <sge/image/traits/format_to_string.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace image
{
namespace traits
{

template<>
struct format_to_string<
	sge::image::ds::tag
>
{
	SGE_IMAGE_DS_SYMBOL
	static
	fcppt::string
	execute(
		sge::image::ds::format
	);
};

}
}
}

#endif
