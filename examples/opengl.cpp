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


#include <sge/image/color/format.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/opengl/buffer/base.hpp>
#include <sge/renderer/opengl/texture/base.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/dont_manage.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/title.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge opengl example")
					),
					sge::window::dim(
						1024,
						768
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::viewport::dont_manage()
			)
			.name(
				FCPPT_TEXT("opengl")
			)
		)
	);

	sge::renderer::texture::planar_scoped_ptr const texture(
		sys.renderer().create_planar_texture(
			sge::renderer::texture::planar_parameters(
				sge::renderer::dim2(
					256,
					256
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags::none,
				sge::renderer::texture::capabilities_field::null()
			)
		)
	);

	sge::renderer::opengl::texture::base const *const opengl_texture(
		dynamic_cast<
			sge::renderer::opengl::texture::base const *
		>(
			texture.get()
		)
	);

	if(
		!opengl_texture
	)
		fcppt::io::cout()
			<< FCPPT_TEXT("Not an opengl texture!\n");
	else
		fcppt::io::cout()
			<< FCPPT_TEXT("Opengl texture id is ")
			<< opengl_texture->id()
			<< FCPPT_TEXT('\n');

	typedef sge::renderer::vf::part<
		boost::mpl::vector1<
			sge::renderer::vf::pos<
				float,
				3
			>
		>
	> vf_part;

	typedef sge::renderer::vf::format<
		boost::mpl::vector1<
			vf_part
		>
	> vf_format;

	sge::renderer::vertex_declaration_scoped_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<
				vf_format
			>()
		)
	);

	sge::renderer::vertex_buffer_scoped_ptr const vertex_buffer(
		sys.renderer().create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::make_part_index<
				vf_format,
				vf_part
			>(),
			sge::renderer::vertex_count(
				3u
			),
			sge::renderer::resource_flags::none
		)
	);

	sge::renderer::opengl::buffer::base const *const opengl_buffer(
		dynamic_cast<
			sge::renderer::opengl::buffer::base const *
		>(
			vertex_buffer.get()
		)
	);

	if(
		!opengl_buffer
	)
		fcppt::io::cout()
			<< FCPPT_TEXT("Not an opengl buffer!\n");
	else
		fcppt::io::cout()
			<< FCPPT_TEXT("Opengl buffer id is ")
			<< opengl_buffer->id()
			<< FCPPT_TEXT(" and native is ")
			<< std::boolalpha
			<< opengl_buffer->native()
			<< FCPPT_TEXT('\n');
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
