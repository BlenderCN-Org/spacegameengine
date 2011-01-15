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


#ifndef SGE_IMAGE_VIEW_DATA_VISITOR_HPP_INCLUDED
#define SGE_IMAGE_VIEW_DATA_VISITOR_HPP_INCLUDED

#include <mizuiro/image/is_raw_view.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace image
{
namespace view
{

template<
	typename Dst
>
struct data_visitor
{
	typedef Dst result_type;

	// This overload is currently not needed
	template<
		typename Src
	>
	typename boost::disable_if<
		mizuiro::image::is_raw_view<
			Src
		>,
		result_type
	>::type
	operator()(
		Src const &_src
	) const
	{
		// casting to a byte buffer is ok
		return
			reinterpret_cast<
				Dst
			>(
				_src.data()
			);
	}

	template<
		typename Src
	>
	typename boost::enable_if<
		mizuiro::image::is_raw_view<
			Src
		>,
		result_type
	>::type
	operator()(
		Src const &_src
	) const
	{
		return _src.data().get();
	}
};

}
}
}

#endif
