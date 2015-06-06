/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/fbo/config.hpp>
#include <sge/opengl/fbo/delete_id.hpp>
#include <sge/opengl/fbo/id.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::fbo::delete_id(
	sge::opengl::fbo::config const &_context,
	sge::opengl::fbo::id const _id
)
{
	GLuint const id(
		_id.get()
	);

	_context.delete_framebuffers()(
		1,
		&id
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDeleteFramebuffers failed"),
		sge::renderer::exception
	)
}
