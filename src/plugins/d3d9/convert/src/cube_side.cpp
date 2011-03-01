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


#include "../cube_side.hpp"
#include "../../d3dinclude.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

D3DCUBEMAP_FACES
sge::d3d9::convert::cube_side(
	sge::renderer::texture::cube_side::type const _side
)
{
	switch(
		_side
	)
	{
	case sge::renderer::texture::cube_side::front:
		return D3DCUBEMAP_FACE_NEGATIVE_Z;
	case sge::renderer::texture::cube_side::back:
		return D3DCUBEMAP_FACE_POSITIVE_Z;
	case sge::renderer::texture::cube_side::left:
		return D3DCUBEMAP_FACE_NEGATIVE_X;
	case sge::renderer::texture::cube_side::right:
		return D3DCUBEMAP_FACE_POSITIVE_X;
	case sge::renderer::texture::cube_side::top:
		return D3DCUBEMAP_FACE_POSITIVE_Y;
	case sge::renderer::texture::cube_side::bottom:
		return D3DCUBEMAP_FACE_NEGATIVE_Y;
	case sge::renderer::texture::cube_side::size:
		break;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid cube_side!")
	);
}
