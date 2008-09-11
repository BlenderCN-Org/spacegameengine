/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../uniform_variable.hpp"
#include "../uniform_variable_functions.hpp"
#include "../uniform_setter.hpp"
#include "../uniform_get.hpp"
#include "../../error.hpp"
#include <boost/variant/apply_visitor.hpp>

template<bool Native>
sge::ogl::glsl::uniform_variable<Native>::uniform_variable(
	handle const program,
	renderer::glsl::string const &name)
:
	ref(
		get_uniform_location<Native>(
			program,
			name.c_str())),
	stored_type(
		uniform_type::nothing)
{}

template<bool Native>
void sge::ogl::glsl::uniform_variable<Native>::set(
	renderer::glsl::uniform_value const &v)
{
	SGE_OPENGL_SENTRY
	stored_type = boost::apply_visitor(
		uniform_setter(
			location()),
		v);
}

template<bool Native>
sge::renderer::glsl::uniform_value const
sge::ogl::glsl::uniform_variable<Native>::get() const
{
	return uniform_get(
		stored_type);
}

template<bool Native>
GLint sge::ogl::glsl::uniform_variable<Native>::location() const
{
	return ref;
}

template class sge::ogl::glsl::uniform_variable<true>;
template class sge::ogl::glsl::uniform_variable<false>;
