/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../init.hpp"
#include "../../glew.hpp"
#include "../../version.hpp"
#include "../../common.hpp"
#include <sge/once.hpp>
#include <sge/text.hpp>

namespace
{

bool native;

void initialize_glsl();

}

bool sge::ogl::glsl::is_native()
{
	initialize_glsl();
	return native;
}

namespace
{

void initialize_glsl()
{
	SGE_FUNCTION_ONCE

	if(sge::ogl::glew_is_supported("GL_VERSION_2_0"))
		native = true;
	else if(sge::ogl::glew_is_supported("GL_ARB_vertex_shader GL_ARB_fragment_shader"))
		native = false;
	else
		sge::ogl::on_not_supported(
			SGE_TEXT("shader"),
			SGE_TEXT("2.0"),
			SGE_TEXT("gl_arb_vertex_shader && gl_arb_fragment_shader"));
}

}
