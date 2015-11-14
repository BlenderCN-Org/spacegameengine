/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/create_cube.hpp>
#include <sge/opengl/texture/cube.hpp>
#include <sge/opengl/texture/cube_context.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::texture::cube_unique_ptr
sge::opengl::texture::create_cube(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::renderer::texture::cube_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::texture::cube
		>(
			fcppt::make_unique_ptr<
				sge::opengl::texture::cube
			>(
				fcppt::optional_to_exception(
					sge::opengl::context::use<
						sge::opengl::texture::cube_context
					>(
						_basic_parameters.context(),
						_basic_parameters.context().info()
					).config(),
					[]{
						return
							sge::renderer::unsupported{
								FCPPT_TEXT("cube texture"),
								FCPPT_TEXT("1.3"),
								FCPPT_TEXT("gl_arb_texture_cube")
							};
					}
				),
				_basic_parameters,
				_parameters
			)
		);
}
