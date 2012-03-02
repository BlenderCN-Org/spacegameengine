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


#include <sge/renderer/glsl/uniform/int_type.hpp>
#include <sge/renderer/glsl/uniform/int_value.hpp>
#include <sge/renderer/glsl/uniform/int_value_type.hpp>
#include <sge/src/renderer/glsl/uniform/instantiate_basic_value.hpp>


SGE_RENDERER_GLSL_UNIFORM_INSTANTIATE_BASIC_VALUE(
	sge::renderer::glsl::uniform::int_type,
	sge::renderer::glsl::uniform::int_value_type::type
);
