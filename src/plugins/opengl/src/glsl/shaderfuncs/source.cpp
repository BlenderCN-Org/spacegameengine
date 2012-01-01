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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/glsl/instantiate.hpp>
#include <sge/opengl/glsl/shader_contexts.hpp>
#include <sge/opengl/glsl/shaderfuncs/source.hpp>
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>


template<
	typename Environment
>
void
sge::opengl::glsl::shaderfuncs::source(
	typename Environment::shader_context const &_context,
	typename Environment::handle const _handle,
	GLint const _num_strings,
	typename Environment::char_ const **const _strings,
	GLint const *const _len_of_strings
)
{
	_context.shader_source()(
		_handle,
		_num_strings,
		_strings,
		_len_of_strings
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Setting a glsl shader source failed"),
		sge::renderer::glsl::exception
	)
}

#define SGE_OPENGL_GLSL_SHADERFUNCS_INSTANTIATE_SOURCE(\
	env\
)\
template \
void \
sge::opengl::glsl::shaderfuncs::source<\
	env\
>(\
	env::shader_context const &,\
	env::handle,\
	GLint,\
	env::char_ const **,\
	GLint const *\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_SHADERFUNCS_INSTANTIATE_SOURCE
)
