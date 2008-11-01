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


#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <boost/gil/extension/dynamic_image/algorithm.hpp>

struct in_place_converter {
	template<
		typename Src,
		typename Dest
	>
	void operator()(
		Src const &src,
		Dest &dest) const
	{
		Dest cp;
		boost::gil::default_color_converter()(
			src,
			cp);
		dest = cp;
	}
};

void sge::renderer::copy_and_convert_pixels(
	const_image_view const &src,
	image_view const &dest)
{
	boost::gil::copy_and_convert_pixels(
		src,
		dest);
		//,
		//in_place_converter());
}
