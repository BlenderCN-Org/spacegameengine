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


#include <sge/cg/string.hpp>
#include <sge/cg/context/object.hpp>
#include <sge/cg/parameter/named.hpp>
#include <sge/cg/parameter/object.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/cg/program/from_string_parameters.hpp>
#include <sge/cg/program/main_function.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/cg/program/source_type.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/const_vertex_buffer_ref_container.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/scoped_vertex_declaration_and_buffers.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <sge/renderer/cg/loaded_program_scoped_ptr.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/cg/loaded_texture_scoped_ptr.hpp>
#include <sge/renderer/cg/scoped_program.hpp>
#include <sge/renderer/cg/scoped_texture.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vf/extra.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge cg point sprites test")
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
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::off,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::yes
					),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<
						sge::media::extension_set
					>
					(
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					)
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_option_field::null()
			)
		)
	);

	typedef sge::renderer::vf::pos<
		float,
		3
	> pos3_type;

	typedef sge::renderer::vf::texpos<
		float,
		2,
		sge::renderer::vf::index<
			0u
		>
	> texpos_type;

	typedef sge::renderer::vf::extra<
		sge::renderer::vf::vector<
			float,
			1u
		>,
		sge::renderer::vf::index<
			0u
		>
	> point_size_type;

	typedef sge::renderer::vf::part<
		boost::mpl::vector3<
			pos3_type,
			texpos_type,
			point_size_type
		>
	> format_part;

	typedef sge::renderer::vf::format<
		boost::mpl::vector1<
			format_part
		>
	> format;

	sge::renderer::vertex_declaration_scoped_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<
				format
			>()
		)
	);

	sge::cg::context::object const cg_context;

	sge::cg::profile::object const vertex_profile(
		sys.renderer().create_cg_profile(
			sge::cg::profile::shader_type::vertex
		)
	);

	sge::cg::string const vertex_shader_source(
		"struct vertex_outputs\n"
		"{\n"
		"	float2 position : POSITION;\n"
		"	float point_size : PSIZE;\n"
		"	float2 external_texpos : COLOR0;\n"
		"};\n"
		"vertex_outputs\n"
		"vertex_main(\n"
		"	float2 position : POSITION,\n"
		"	float2 texpos : TEXCOORD0,\n"
		"	float point_size : $0$\n"
		")\n"
		"{\n"
		"	vertex_outputs outs;\n"
		"	outs.position = float4(position,0.0,1.0);\n"
		"	outs.point_size = point_size;\n"
		"	outs.external_texpos = texpos;\n"
		"	return outs;\n"
		"}\n"
	);

	sge::cg::string const pixel_shader_source(
		"float4\n"
		"pixel_main(\n"
		"	float2 external_texpos : COLOR0,\n"
		"	float2 texCoord : TEXCOORD0,\n"
		"	uniform sampler2D decal : TEX0\n"
		") : COLOR\n"
		"{\n"
		"	return tex2D(decal,external_texpos.xy + texCoord.xy / 2.0);\n"
		"}\n"
	);

	sge::cg::program::object vertex_program(
		sge::cg::program::from_string_parameters(
			cg_context,
			sge::cg::program::source_type::text,
			vertex_profile,
			sys.renderer().transform_cg_vertex_program(
				*vertex_declaration,
				sge::cg::program::source(
					vertex_shader_source
				)
			),
			sge::cg::program::main_function(
				"vertex_main"
			),
			sys.renderer().cg_compile_options(
				cg_context,
				vertex_profile
			)
		)
	);

	sge::renderer::cg::loaded_program_scoped_ptr const loaded_vertex_program(
		sys.renderer().load_cg_program(
			vertex_program
		)
	);

	sge::cg::profile::object const pixel_profile(
		sys.renderer().create_cg_profile(
			sge::cg::profile::shader_type::pixel
		)
	);

	sge::cg::program::object pixel_program(
		sge::cg::program::from_string_parameters(
			cg_context,
			sge::cg::program::source_type::text,
			pixel_profile,
			sge::cg::program::source(
				pixel_shader_source
			),
			sge::cg::program::main_function(
				"pixel_main"
			),
			sys.renderer().cg_compile_options(
				cg_context,
				pixel_profile
			)
		)
	);

	sge::renderer::cg::loaded_program_scoped_ptr const loaded_pixel_program(
		sys.renderer().load_cg_program(
			pixel_program
		)
	);

	sge::renderer::vertex_buffer_scoped_ptr const vertex_buffer(
		sys.renderer().create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::make_part_index<
				format,
				format_part
			>(),
			sge::renderer::vertex_count(
				1u
			),
			sge::renderer::resource_flags_field::null()
		)
	);

	{
		sge::renderer::scoped_vertex_lock const vblock(
			*vertex_buffer,
			sge::renderer::lock_mode::writeonly
		);

		typedef sge::renderer::vf::view<
			format_part
		> vertex_view;

		vertex_view const vertices(
			vblock.value()
		);

		vertex_view::iterator vb_it(
			vertices.begin()
		);

		typedef pos3_type::packed_type pos3;
		typedef texpos_type::packed_type texpos;
		typedef point_size_type::packed_type point_size;


		(*vb_it).set<
			pos3_type
		>(
			pos3(
				0.f,
				0.f,
				0.f
			)
		);

		(*vb_it).set<
			texpos_type
		>(
			texpos(
				0.5f,
				0.5f
			)
		);

		(*vb_it).set<
			point_size_type
		>(
			point_size(
				200.0f
			)
		);
	}

	sge::renderer::texture::planar_scoped_ptr const texture(
		sge::renderer::texture::create_planar_from_path(
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("uvtestgrid.png"),
			sys.renderer(),
			sys.image_system(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null()
		)
	);

	sge::renderer::cg::loaded_texture_scoped_ptr const loaded_texture(
		sys.renderer().load_cg_texture(
			pixel_program.parameter(
				"decal"
			).object(),
			*texture
		)
	);

	fcppt::signal::scoped_connection const input_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	while(
		sys.window_system().poll()
	)
	{
		sge::renderer::context::scoped const scoped_block(
			sys.renderer(),
			sys.renderer().onscreen_target()
		);

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::blue()
			)
		);

		sge::renderer::scoped_vertex_declaration_and_buffers const vb_context(
			scoped_block.get(),
			*vertex_declaration,
			fcppt::assign::make_container<
				sge::renderer::const_vertex_buffer_ref_container
			>(
				fcppt::cref(
					*vertex_buffer
				)
			)
		);

		sge::renderer::cg::scoped_program const scoped_vertex_program(
			scoped_block.get(),
			*loaded_vertex_program
		);

		sge::renderer::cg::scoped_program const scoped_pixel_program(
			scoped_block.get(),
			*loaded_pixel_program
		);

		sge::renderer::cg::scoped_texture const scoped_texture(
			scoped_block.get(),
			*loaded_texture
		);

		scoped_block.get().state(
			sge::renderer::state::list
				(sge::renderer::state::bool_::enable_point_sprites = true));

		scoped_block.get().render_nonindexed(
			sge::renderer::first_vertex(
				0u
			),
			vertex_buffer->size(),
			sge::renderer::primitive_type::point_list
		);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.what()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
