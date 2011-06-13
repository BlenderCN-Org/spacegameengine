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


#include "../color_format.hpp"
#include "../../d3dinclude.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

D3DFORMAT
sge::d3d9::convert::color_format(
	sge::image::color::format::type const _format
)
{
	switch(
		_format
	)
	{
	case sge::image::color::format::alpha8:
		return D3DFMT_A8;
	case sge::image::color::format::gray8:
		return D3DFMT_L8;
	case sge::image::color::format::rgba8:
	case sge::image::color::format::argb8:
	case sge::image::color::format::bgra8:
		return D3DFMT_A8R8G8B8;
	case sge::image::color::format::rgb8:
		return D3DFMT_R8G8B8;
	case sge::image::color::format::rgba32f:
	case sge::image::color::format::argb32f:
	case sge::image::color::format::bgra32f:
	case sge::image::color::format::rgb32f:
		return D3DFMT_A32B32G32R32F;
	case sge::image::color::format::ag8:
	case sge::image::color::format::ga8:
		return D3DFMT_A8L8;
	case sge::image::color::format::size:
		break;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid color_format!")
	);
}
