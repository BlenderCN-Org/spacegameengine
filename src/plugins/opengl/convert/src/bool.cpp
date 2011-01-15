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


#include "../bool.hpp"
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

GLenum
sge::opengl::convert::bool_(
	renderer::state::bool_::type const _state
)
{
	namespace rs = renderer::state::bool_::available_states;

	switch(
		_state.state()
	)
	{
	case rs::enable_alpha_blending:
		return GL_BLEND;
	case rs::enable_lighting:
		return GL_LIGHTING;
	case rs::enable_scissor_test:
		return GL_SCISSOR_TEST;
	case rs::clear_backbuffer:
	case rs::clear_zbuffer:
	case rs::clear_stencil:
	case rs::enable_multi_sampling:
	case rs::enable_point_sprites:
	case rs::write_to_zbuffer:
		break;
	}

	throw renderer::exception(
		FCPPT_TEXT("Invalid bool_state!")
	);
}
