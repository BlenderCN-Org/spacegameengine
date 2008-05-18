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


#ifndef SGE_OPENGL_GLSL_UNIFORM_VARIABLE_HPP_INCLUDED
#define SGE_OPENGL_GLSL_UNIFORM_VARIABLE_HPP_INCLUDED

#include "traits.hpp"
#include "../common.hpp"
#include <sge/math/vector.hpp>
#include <sge/math/matrix.hpp>
#include <sge/renderer/glsl_uniform_variable.hpp>
#include <string>

namespace sge
{
namespace ogl
{
namespace glsl
{

template<bool Native>
class uniform_variable : public sge::glsl::uniform_variable {
public:
	typedef typename traits<Native>::handle handle;
	uniform_variable(
		handle program,
		const std::string& name);

	void set(space_unit);
	void set(const math::vector2&);
	void set(const math::vector3&);
	void set(const math::vector4&);

	void set(const math::space_matrix&);
private:
	GLint location() const;
	handle ref;
};

}
}
}

#endif
