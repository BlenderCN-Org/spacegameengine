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


#ifndef SGE_GUI_CREATE_TEXTURE_HPP_INCLUDED
#define SGE_GUI_CREATE_TEXTURE_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>


namespace sge
{
namespace gui
{

SGE_GUI_DETAIL_SYMBOL
sge::renderer::texture::planar_unique_ptr
create_texture(
	sge::renderer::device::core &,
	sge::image2d::view::const_object const &
);

}
}

#endif
