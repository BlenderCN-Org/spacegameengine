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


#include "../depth_stencil_format_to_attachment.hpp"
#include "../context.hpp"
#include "../../common.hpp"
#include <sge/renderer/depth_stencil_format.hpp>
#include <fcppt/assert/unreachable.hpp>

GLenum
sge::opengl::fbo::depth_stencil_format_to_attachment(
	fbo::context const &_context,
	renderer::depth_stencil_format::type const _format
)
{
	switch(
		_format
	)
	{
	case renderer::depth_stencil_format::d16:
	case renderer::depth_stencil_format::d32:
		return _context.depth_attachment();
	case renderer::depth_stencil_format::d24s8:
		return _context.depth_stencil_attachment();
	}

	FCPPT_ASSERT_UNREACHABLE;
}
