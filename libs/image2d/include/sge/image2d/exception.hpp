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


#ifndef SGE_IMAGE2D_EXCEPTION_HPP_INCLUDED
#define SGE_IMAGE2D_EXCEPTION_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/exception.hpp>
#include <sge/image2d/exception_fwd.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>


namespace sge
{
namespace image2d
{

class SGE_CORE_DETAIL_CLASS_SYMBOL exception
:
	public sge::image::exception
{
public:
	SGE_IMAGE2D_DETAIL_SYMBOL
	explicit
	exception(
		fcppt::string &&
	);

	SGE_IMAGE2D_DETAIL_SYMBOL
	explicit
	exception(
		fcppt::assert_::information const &
	);

	SGE_IMAGE2D_DETAIL_SYMBOL
	exception(
		exception &&
	);

	SGE_IMAGE2D_DETAIL_SYMBOL
	exception(
		exception const &
	);

	SGE_IMAGE2D_DETAIL_SYMBOL
	exception &
	operator=(
		exception &&
	);

	SGE_IMAGE2D_DETAIL_SYMBOL
	exception &
	operator=(
		exception const &
	);

	SGE_IMAGE2D_DETAIL_SYMBOL
	~exception() noexcept
	override;
};

}
}

#endif
