/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_IMAGE_INVALID_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_INVALID_CONVERT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/exception.hpp>
#include <sge/image/invalid_convert_fwd.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>


namespace sge
{
namespace image
{

template<
	typename Tag
>
class SGE_CORE_DETAIL_CLASS_SYMBOL invalid_convert
:
	public sge::image::exception
{
public:
	typedef
	sge::image::traits::pixel::format<
		Tag
	>
	format;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	invalid_convert(
		format source,
		format dest
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	invalid_convert(
		invalid_convert &&
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	invalid_convert(
		invalid_convert const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	invalid_convert &
	operator=(
		invalid_convert &&
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	invalid_convert &
	operator=(
		invalid_convert const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	~invalid_convert() noexcept
	override;
};

}
}

#endif
