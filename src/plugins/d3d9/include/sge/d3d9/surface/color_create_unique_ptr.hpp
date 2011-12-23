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


#ifndef SGE_D3D9_SURFACE_COLOR_CREATE_UNIQUE_PTR_HPP_INCLUDED
#define SGE_D3D9_SURFACE_COLOR_CREATE_UNIQUE_PTR_HPP_INCLUDED

#include <sge/d3d9/surface/color_create_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sge
{
namespace d3d9
{
namespace surface
{

typedef fcppt::unique_ptr<
	surface::color_create
> color_create_unique_ptr;

}
}
}

#endif
