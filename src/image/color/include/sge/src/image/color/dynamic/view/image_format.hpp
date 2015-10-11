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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_VIEW_IMAGE_FORMAT_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_VIEW_IMAGE_FORMAT_HPP_INCLUDED


namespace sge
{
namespace image
{
namespace color
{
namespace dynamic
{
namespace view
{

template<
	typename View
>
typename
View::format
image_format(
	View const &_view
)
{
	return
		_view.format_store().get().get();
}

}
}
}
}
}

#endif
