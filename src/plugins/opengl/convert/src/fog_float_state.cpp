/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../fog_float_state.hpp"
#include <sge/renderer/state/var.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

GLenum
sge::opengl::convert::fog_float_state(
	renderer::state::float_::type const &s
)
{
	namespace rs = renderer::state::float_::available_states;

	switch(s.state()) {
	case rs::fog_start:
		return GL_FOG_START;
	case rs::fog_end:
		return GL_FOG_END;
	case rs::fog_density:
		return GL_FOG_DENSITY;
	case rs::zbuffer_clear_val:
	case rs::alpha_test_ref:
		break;
	}

	throw exception(
		FCPPT_TEXT("Invalid fog float_state!")
	);
}
