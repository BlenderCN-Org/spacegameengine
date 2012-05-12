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


#include <sge/renderer/unsupported.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/create_cube.hpp>
#include <sge/opengl/texture/cube.hpp>
#include <sge/opengl/texture/cube_context.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_unique_ptr.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>


sge::renderer::texture::cube_unique_ptr
sge::opengl::texture::create_cube(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::texture::cube_parameters const &_parameters
)
{
	if(
		!sge::opengl::context::use<
			sge::opengl::texture::cube_context
		>(
			_system_context
		).have_cube_texture()
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("cube texture"),
			FCPPT_TEXT("1.3"),
	       		FCPPT_TEXT("gl_arb_texture_cube")
		);

	return
		sge::renderer::texture::cube_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::texture::cube
			>(
				fcppt::ref(
					_system_context
				),
				fcppt::cref(
					_parameters
				)
			)
		);
}
