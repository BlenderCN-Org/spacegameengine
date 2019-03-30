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


#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/fbo/config.hpp>
#include <sge/opengl/fbo/gen_render_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


GLuint
sge::opengl::fbo::gen_render_buffer(
	sge::opengl::fbo::config const &_config
)
{
	GLuint id;

	sge::opengl::call_fun_ref(
		_config.gen_renderbuffers(),
		1,
		&id
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Generating a render buffer failed."),
		sge::renderer::exception
	)

	return
		id;
}
