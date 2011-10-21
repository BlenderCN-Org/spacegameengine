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


#include "../create.hpp"
#include "../../program_contexts.hpp"
#include "../../instantiate.hpp"
#include "../../../check_state.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>


template<
	typename Environment
>
typename Environment::handle
sge::opengl::glsl::programfuncs::create(
	typename Environment::program_context const &_context
)
{
	typename Environment::handle const ret(
		_context.create_program()()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Creating a glsl program failed"),
		sge::renderer::glsl::exception
	)

	return ret;
}

#define SGE_OPENGL_GLSL_PROGRAMFUNCS_INSTANTIATE_CREATE(\
	env\
)\
template \
env::handle \
sge::opengl::glsl::programfuncs::create<\
	env\
>(\
	env::program_context const &\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_PROGRAMFUNCS_INSTANTIATE_CREATE
)
