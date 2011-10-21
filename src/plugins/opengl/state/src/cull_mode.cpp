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


#include "../cull_mode.hpp"
#include "../parameters_fwd.hpp"
#include "../convert/cull_mode.hpp"
#include "../../check_state.hpp"
#include "../../common.hpp"
#include "../../enable.hpp"
#include "../../disable.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::state::cull_mode(
	state::parameters const &,
	renderer::state::cull_mode::type const _mode
)
{
	if(
		_mode == renderer::state::cull_mode::off
	)
	{
		opengl::disable(
			GL_CULL_FACE
		);

		return;
	}

	opengl::enable(
		GL_CULL_FACE
	);

	::glCullFace(
		state::convert::cull_mode(
			_mode
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glCullFace failed"),
		sge::renderer::exception
	)
}
