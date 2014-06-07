/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/fbo/attach_render_buffer.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::fbo::attach_render_buffer(
	sge::opengl::fbo::context const &_context,
	sge::opengl::fbo::attachment_type const _what,
	GLuint const _buffer
)
{
	_context.framebuffer_renderbuffer()(
		_context.framebuffer_target(),
		_what.get(),
		_context.renderbuffer_target(),
		_buffer
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Attaching a render buffer to a frame buffer failed!"),
		sge::renderer::exception
	)
}
