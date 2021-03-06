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


#ifndef SGE_RENDERER_TEXTURE_CREATION_FAILED_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CREATION_FAILED_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL creation_failed
:
	public sge::renderer::exception
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	creation_failed(
		fcppt::string &&
	);

	SGE_RENDERER_DETAIL_SYMBOL
	creation_failed(
		creation_failed &&
	);

	SGE_RENDERER_DETAIL_SYMBOL
	creation_failed(
		creation_failed const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	creation_failed &
	operator=(
		creation_failed &&
	);

	SGE_RENDERER_DETAIL_SYMBOL
	creation_failed &
	operator=(
		creation_failed const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~creation_failed() noexcept
	override;
};

}
}
}

#endif
