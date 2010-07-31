/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../fbo_target.hpp"
#include "../fbo_functions.hpp"
#include "../on_not_supported.hpp"
#include "../texture_base.hpp"
#include "../check_state.hpp"
#include <sge/renderer/texture.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/shared_ptr.hpp>
#include <fcppt/text.hpp>

sge::opengl::fbo_target::fbo_target(
	sge::renderer::parameters const &param_,
	opengl::texture_ptr const texture_
)
:
	fbo_()
{
	if(!glGenFramebuffersEXT)
		on_not_supported(
			FCPPT_TEXT("glGenFrameBuffersEXT"),
			FCPPT_TEXT("none"),
			FCPPT_TEXT("frame_buffer_ext")
		);

	glGenFramebuffersEXT(1, &fbo);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGenFramebuffersEXT failed"),
		sge::renderer::exception
	)

	bind_me();
}

sge::opengl::fbo_target::~fbo_target()
{
	glDeleteFramebuffersEXT(1, &fbo);
}

void sge::opengl::fbo_target::bind_me() const
{
	bind_fbo(fbo);
}

void sge::opengl::fbo_target::bind_texture(
	renderer::texture_ptr const t)
{
	bind_me();

	fcppt::shared_ptr<texture_base> const p(
		fcppt::dynamic_pointer_cast<texture_base>(t));

	glFramebufferTexture2DEXT(
		GL_FRAMEBUFFER_EXT,
		GL_COLOR_ATTACHMENT0_EXT,
		GL_TEXTURE_2D,
		p->id(),
		0);

	GLenum const status(
		glCheckFramebufferStatusEXT(
			GL_FRAMEBUFFER_EXT
		)
	);

	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
		throw renderer::exception(
			FCPPT_TEXT("glCheckFramebufferStatusEXT: fbo incomplete!"));

	texture_target = fcppt::dynamic_pointer_cast<texture>(t);
}

sge::renderer::target::dim_type const
sge::opengl::fbo_target::dim() const
{
	return texture_target->dim();
}

sge::renderer::pixel_pos const
sge::opengl::fbo_target::pos() const
{
	return renderer::pixel_pos::null();
}

sge::opengl::fbo_target::size_type
sge::opengl::fbo_target::stride() const
{
	return texture_target->stride();
}

GLenum sge::opengl::fbo_target::format() const
{
	return texture_target->format();
}

GLenum sge::opengl::fbo_target::format_type() const
{
	return texture_target->format_type();
}
