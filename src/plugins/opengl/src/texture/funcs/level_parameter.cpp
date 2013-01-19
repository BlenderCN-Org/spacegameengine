/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/funcs/level_parameter.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/text.hpp>


GLint
sge::opengl::texture::funcs::level_parameter(
	sge::opengl::texture::binding const &,
	sge::opengl::texture::buffer_type const _type,
	sge::renderer::texture::mipmap::level const _level,
	GLenum const _what
)
{
	GLint ret;

	::glGetTexLevelParameteriv(
		_type.get(),
		static_cast<
			GLint
		>(
			_level.get()
		),
		_what,
		&ret
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGetTexLevelParameteriv() failed!"),
		sge::renderer::exception
	);

	return ret;
}
