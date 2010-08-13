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


#include "../fbo_context.hpp"
#include "../common.hpp"
#include "../glew/is_supported.hpp"
#include "../context/make_id.hpp"

sge::opengl::fbo_context::fbo_context()
:
	has_native_(
		glew::is_supported("GL_VERSION_3_0")
	),
	has_ext_(
		glew::is_supported("gl_framebuffer_ext")
	),
	gen_framebuffers_(
		has_native_
		?
			glGenFramebuffers
		:
			has_ext_
			?
				glGenFramebuffersEXT
			:
				0
	),
	delete_framebuffers_(
		has_native_
		?
			glDeleteFramebuffers
		:
			has_ext_
			?
				glDeleteFramebuffersEXT
			:
				0
	),
	bind_framebuffer_(
		has_native_
		?
			glBindFramebuffer
		:
			has_ext_
			?
				glBindFramebufferEXT
			:
				0
	),
	framebuffer_texture_2d_(
		has_native_
		?
			glFramebufferTexture2D
		:
			has_ext_
			?
				glFramebufferTexture2DEXT
			:
				0
	),
	check_framebuffer_status_(
		has_native_
		?
			glCheckFramebufferStatus
		:
			has_ext_
			?
				glCheckFramebufferStatusEXT
			:
				0
	),
	gen_renderbuffers_(
		has_native_
		?
			glGenRenderbuffers
		:
			has_ext_
			?
				glGenRenderbuffersEXT
			:
				0
	),
	delete_renderbuffers_(
		has_native_
		?
			glDeleteRenderbuffers
		:
			has_ext_
			?
				glDeleteRenderbuffersEXT
			:
				0
	),
	bind_renderbuffer_(
		has_native_
		?
			glBindRenderbuffer
		:
			has_ext_
			?
				glBindRenderbufferEXT
			:
				0
	),
	renderbuffer_storage_(
		has_native_
		?
			glRenderbufferStorage
		:
			has_ext_
			?
				glRenderbufferStorageEXT
			:
				0
	),
	framebuffer_renderbuffer_(
		has_native_
		?
			glFramebufferRenderbuffer
		:
			has_ext_
			?
				glFramebufferRenderbufferEXT
			:
				0
	),
	framebuffer_target_(
		has_native_
		?
			GL_FRAMEBUFFER
		:
			has_ext_
			?
				GL_FRAMEBUFFER_EXT
			:
				0
	),
	color_attachment_(
		has_native_
		?
			GL_COLOR_ATTACHMENT0
		:
			has_ext_
			?
				GL_COLOR_ATTACHMENT0_EXT
			:
				0
	),
	framebuffer_complete_(
		has_native_
		?
			GL_FRAMEBUFFER_COMPLETE
		:
			has_ext_
			?
				GL_FRAMEBUFFER_COMPLETE_EXT
			:
				0
	),
	renderbuffer_target_(
		has_native_
		?
			GL_RENDERBUFFER
		:
			has_ext_
			?
				GL_RENDERBUFFER_EXT
			:
				0
	),
	depth_attachment_(
		has_native_
		?
			GL_DEPTH_ATTACHMENT
		:
			has_ext_
			?
				GL_DEPTH_ATTACHMENT_EXT
			:
				0
	),
	stencil_attachment_(
		has_native_
		?
			GL_STENCIL_ATTACHMENT
		:
			has_ext_
			?
				GL_STENCIL_ATTACHMENT_EXT
			:
				0
	)
{
}

sge::opengl::fbo_context::~fbo_context()
{
}

bool
sge::opengl::fbo_context::is_supported() const
{
	return
		has_native_
		|| has_ext_;
}

sge::opengl::fbo_context::gl_gen_framebuffers
sge::opengl::fbo_context::gen_framebuffers() const
{
	return gen_framebuffers_;
}

sge::opengl::fbo_context::gl_delete_framebuffers
sge::opengl::fbo_context::delete_framebuffers() const
{
	return delete_framebuffers_;
}

sge::opengl::fbo_context::gl_bind_framebuffer
sge::opengl::fbo_context::bind_framebuffer() const
{
	return bind_framebuffer_;
}

sge::opengl::fbo_context::gl_framebuffer_texture_2d
sge::opengl::fbo_context::framebuffer_texture_2d() const
{
	return framebuffer_texture_2d_;
}

sge::opengl::fbo_context::gl_check_framebuffer_status
sge::opengl::fbo_context::check_framebuffer_status() const
{
	return check_framebuffer_status_;
}

sge::opengl::fbo_context::gl_gen_renderbuffers
sge::opengl::fbo_context::gen_renderbuffers() const
{
	return gen_renderbuffers_;
}

sge::opengl::fbo_context::gl_delete_renderbuffers
sge::opengl::fbo_context::delete_renderbuffers() const
{
	return delete_renderbuffers_;
}

sge::opengl::fbo_context::gl_bind_renderbuffer
sge::opengl::fbo_context::bind_renderbuffer() const
{
	return bind_renderbuffer_;
}

sge::opengl::fbo_context::gl_renderbuffer_storage
sge::opengl::fbo_context::renderbuffer_storage() const
{
	return renderbuffer_storage_;
}

sge::opengl::fbo_context::gl_framebuffer_renderbuffer
sge::opengl::fbo_context::framebuffer_renderbuffer() const
{
	return framebuffer_renderbuffer_;
}

GLenum
sge::opengl::fbo_context::framebuffer_target() const
{
	return framebuffer_target_;
}

GLenum
sge::opengl::fbo_context::color_attachment() const
{
	return color_attachment_;
}

GLenum
sge::opengl::fbo_context::framebuffer_complete() const
{
	return framebuffer_complete_;
}

GLenum
sge::opengl::fbo_context::renderbuffer_target() const
{
	return renderbuffer_target_;
}

GLenum
sge::opengl::fbo_context::depth_attachment() const
{
	return depth_attachment_;
}

GLenum
sge::opengl::fbo_context::stencil_attachment() const
{
	return stencil_attachment_;
}

sge::opengl::context::id const
sge::opengl::fbo_context::static_id(
	sge::opengl::context::make_id()
);
