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


#ifndef SGE_RENDERER_VF_DETAIL_RAW_DATA_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_RAW_DATA_HPP_INCLUDED

#include <sge/renderer/const_raw_pointer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace detail
{

template<
	typename T
>
typename boost::disable_if<
	std::is_fundamental<
		T
	>,
	sge::renderer::const_raw_pointer
>::type
raw_data(
	T const &_value
)
{
	return
		reinterpret_cast<
			sge::renderer::const_raw_pointer
		>(
			_value.data()
		);
}

template<
	typename T
>
typename boost::enable_if<
	std::is_fundamental<
		T
	>,
	sge::renderer::const_raw_pointer
>::type
raw_data(
	T const &_value
)
{
	return
		reinterpret_cast<
			sge::renderer::const_raw_pointer
		>(
			&_value
		);
}

}
}
}
}

#endif
