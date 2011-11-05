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


#include <sge/renderer/device.hpp>
#include <sge/renderer/glsl/const_optional_program.hpp>
#include <sge/renderer/glsl/program_fwd.hpp>
#include <sge/renderer/glsl/scoped_program.hpp>


sge::renderer::glsl::scoped_program::scoped_program(
	renderer::device &_rend,
	glsl::program const &_program
)
:
	rend_(
		_rend
	)
{
	rend_.glsl_program(
		sge::renderer::glsl::const_optional_program(
			_program
		)
	);
}

sge::renderer::glsl::scoped_program::~scoped_program()
{
	rend_.glsl_program(
		renderer::glsl::const_optional_program()
	);
}
