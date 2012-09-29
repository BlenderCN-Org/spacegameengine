/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/texture_stage_op.hpp>
#include <sge/renderer/texture/stage_op.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DTEXTURESTAGESTATETYPE
sge::d3d9::convert::texture_stage_op(
	renderer::texture::stage_op::type const _type
)
{
	switch(
		_type
	)
	{
	case renderer::texture::stage_op::color:
		return D3DTSS_COLOROP;
	case renderer::texture::stage_op::alpha:
		return D3DTSS_ALPHAOP;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
