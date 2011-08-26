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


#ifndef SGE_OPENGL_GLSL_UNIFORM_VARIABLE_HPP_INCLUDED
#define SGE_OPENGL_GLSL_UNIFORM_VARIABLE_HPP_INCLUDED

#include "type.hpp"
#include "../../common.hpp"
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace glsl
{
namespace uniform
{

template<
	typename Environment
>
class variable
:
	public renderer::glsl::uniform::variable
{
	FCPPT_NONCOPYABLE(
		variable
	);
public:
	typedef typename Environment::handle handle;

	typedef typename Environment::uniform_context uniform_context;

	explicit variable(
		uniform_context const &,
		handle program,
		renderer::glsl::string const &name
	);

	~variable();

	renderer::glsl::uniform::value const
	get() const;

	void
	set(
		renderer::glsl::uniform::value const &
	);
private:
	uniform_context const &context_;

	handle const program_;

	GLint const location_;

	type stored_type_;
};

}
}
}
}

#endif
