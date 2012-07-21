/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/srgb_context.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/glew/is_supported.hpp>


sge::opengl::srgb_context::srgb_context()
:
	sge::opengl::context::system::base(),
	is_native_(
		sge::opengl::glew::is_supported(
			"GL_VERSION_3_0"
		)
	),
	is_ext_(
		sge::opengl::glew::is_supported(
			"EXT_framebuffer_sRGB"
		)
	),
	flag_(
		static_cast<
			GLenum
		>(
			is_native_
			?
				GL_FRAMEBUFFER_SRGB
			:
				is_ext_
				?
					GL_FRAMEBUFFER_SRGB_EXT
				:
					0
		)
	)
{
}

sge::opengl::srgb_context::~srgb_context()
{
}

bool
sge::opengl::srgb_context::is_supported() const
{
	return
		is_native_
		|| is_ext_;
}

GLenum
sge::opengl::srgb_context::flag() const
{
	return flag_;
}

sge::opengl::context::system::id const
sge::opengl::srgb_context::static_id(
	sge::opengl::context::system::make_id()
);
