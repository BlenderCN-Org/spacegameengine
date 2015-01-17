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


#ifndef SGE_TEXTURE_IMAGE_TOO_BIG_HPP_INCLUDED
#define SGE_TEXTURE_IMAGE_TOO_BIG_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/texture/exception.hpp>
#include <sge/texture/detail/symbol.hpp>


namespace sge
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL image_too_big
:
	public sge::texture::exception
{
public:
	SGE_TEXTURE_DETAIL_SYMBOL
	explicit
	image_too_big(
		sge::renderer::dim2 const &
	);
};

}
}

#endif
