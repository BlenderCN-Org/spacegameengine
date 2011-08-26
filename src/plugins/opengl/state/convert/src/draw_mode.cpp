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


#include "../draw_mode.hpp"
#include "../../../common.hpp"
#include <sge/renderer/state/draw_mode.hpp>
#include <fcppt/assert/unreachable.hpp>

GLenum
sge::opengl::state::convert::draw_mode(
	renderer::state::draw_mode::type const _mode
)
{
	switch(
		_mode
	)
	{
	case renderer::state::draw_mode::point:
		return GL_POINT;
	case renderer::state::draw_mode::line:
		return GL_LINE;
	case renderer::state::draw_mode::fill:
		return GL_FILL;
	}

	FCPPT_ASSERT_UNREACHABLE
}
