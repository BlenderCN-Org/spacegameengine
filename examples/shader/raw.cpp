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


#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/object_impl.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/log/global.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/renderer/target_from_texture.hpp>
#include <sge/renderer/glsl/const_optional_program.hpp>
#include <sge/renderer/glsl/pixel_shader.hpp>
#include <sge/renderer/glsl/pixel_shader_ptr.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/program_ptr.hpp>
#include <sge/renderer/glsl/scoped_attachment.hpp>
#include <sge/renderer/glsl/vertex_shader.hpp>
#include <sge/renderer/glsl/vertex_shader_ptr.hpp>
#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/default_sort.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_depth.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef sge::image::color::rgba8_format sprite_color;

typedef sge::sprite::choices<
	sge::sprite::type_choices<
		int,
		float,
		sprite_color
	>,
	boost::mpl::vector4<
		sge::sprite::with_color,
		sge::sprite::with_texture,
		sge::sprite::with_depth,
		sge::sprite::with_dim
	>
> sprite_choices;

typedef sge::sprite::object<
	sprite_choices
> sprite_object;

class sprite_functor
{
	FCPPT_NONASSIGNABLE(
		sprite_functor
	);
public:
	explicit sprite_functor(
		sprite_object &_sprite
	)
	:
		sprite_(_sprite)
	{}

	void
	operator()(
		sge::input::mouse::axis_event const &_event
	) const
	{
		switch (_event.code())
		{
		case sge::input::mouse::axis_code::x:
			sprite_.x(
				static_cast<sprite_object::unit>(
					sprite_.x() + _event.value()));
			break;
		case sge::input::mouse::axis_code::y:
			sprite_.y(
				static_cast<sprite_object::unit>(
					sprite_.y() + _event.value()));
			break;
		default:
			break;
		}
	}
private:
	sprite_object &sprite_;
};
}

int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	sge::window::dim const window_dim(
		1024,
		768
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge raw glsl shader test")
					),
					window_dim
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
				sge::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				|
				sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive)
			)
		)
		(
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<
						sge::media::extension_set
					>(
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					)
					(
						sge::media::extension(
							FCPPT_TEXT("jpg")
						)
					)
				)
			)
		)
	);

	sge::image2d::file_ptr const
		image_bg(
			sys.image_system().load(
				sge::config::media_path()
				/ FCPPT_TEXT("images")
				/ FCPPT_TEXT("shadertest.jpg")
			)
		),
		image_pointer(
			sys.image_system().load(
				sge::config::media_path()
				/ FCPPT_TEXT("images")
				/ FCPPT_TEXT("cursor.png")
			)
		),
		image_tux(
			sys.image_system().load(
				sge::config::media_path()
				/ FCPPT_TEXT("images")
				/ FCPPT_TEXT("tux.png")
			)
		);

	sge::texture::manager tex_man(
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>(
				fcppt::ref(
					sys.renderer()
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::repeat
				)
			)
		)
	);

	sge::texture::const_part_ptr const
		tex_bg(
			sge::texture::add_image(
				tex_man,
				*image_bg
			)
		),
		tex_pointer(
			sge::texture::add_image(
				tex_man,
				*image_pointer
			)
		),
		tex_tux(
			sge::texture::add_image(
				tex_man,
				*image_tux
			)
		);

	typedef sge::sprite::system<
		sprite_choices
	>::type sprite_system;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_system ss(
		sys.renderer()
	);

	sprite_object bg(
		sprite_parameters()
			.pos(
				sprite_object::vector::null()
			)
			.texture(
				tex_bg
			)
			.size(
				fcppt::math::dim::structure_cast<
					sprite_object::dim
				>(
					window_dim
				)
			)
			.depth(
				static_cast<
					sprite_object::depth_type
				>(0)
			)
			.default_color()
		);

	sprite_object pointer(
		sprite_parameters()
		.pos(
			sprite_object::vector::null()
		)
		.texture(
			tex_pointer
		)
		.texture_size()
		.default_color()
		.depth(
			static_cast<
				sprite_object::depth_type
			>(2)
		)
	);

	sprite_object tux(
		sprite_parameters()
		.pos(
			sprite_object::vector(
 				static_cast<sprite_object::unit>(
					window_dim.w()/2-16),
 				static_cast<sprite_object::unit>(
					window_dim.h()/2-16)
			)
		)
		.texture(
			tex_tux
		)
		.size(
			sprite_object::dim(32,32)
		)
		.default_color()
		.depth(
			static_cast<
				sprite_object::depth_type
			>(1)
		)
	);

	tux.color(
		sge::image::color::rgba8(
			(sge::image::color::init::red() %= 1.0)
			(sge::image::color::init::green() %= 1.0)
			(sge::image::color::init::blue() %= 1.0)
			(sge::image::color::init::alpha() %= 0.25)
		)
	);

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	fcppt::signal::scoped_connection const pc(
		sys.mouse_collector().axis_callback(
			sprite_functor(
				pointer
			)
		)
	);

	sys.renderer().state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(sge::renderer::state::depth_func::off)
			(sge::renderer::state::color::back_buffer_clear_color = sge::image::colors::black()));

	sge::renderer::texture::planar_ptr const target_texture(
		sys.renderer().create_planar_texture(
			sge::renderer::texture::planar_parameters(
				fcppt::math::dim::structure_cast<
					sge::renderer::dim2
				>(
					window_dim
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::clamp
				),
				sge::renderer::resource_flags::none,
				sge::renderer::texture::capabilities_field(
					sge::renderer::texture::capabilities::render_target
				)
			)
		)
	);

	sge::renderer::target_ptr const target(
		sge::renderer::target_from_texture(
			sys.renderer(),
			*target_texture
		)
	);

	sprite_object target_spr(
		sprite_parameters()
		.pos(
			sprite_object::vector::null()
		)
		.texture(
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				target_texture
			)
		)
		.texture_size()
		.default_color()
		.depth(
			static_cast<
				sprite_object::depth_type
			>(1)
		)
	);

	fcppt::io::cifstream fragment_stream(
		sge::config::media_path()
		/ FCPPT_TEXT("shaders")
		/ FCPPT_TEXT("raw")
		/ FCPPT_TEXT("fragment.glsl")
	);

	fcppt::io::cifstream vertex_stream(
		sge::config::media_path()
		/ FCPPT_TEXT("shaders")
		/ FCPPT_TEXT("raw")
		/ FCPPT_TEXT("vertex.glsl")
	);

	sge::renderer::glsl::program_ptr const program(
		sys.renderer().create_glsl_program()
	);

	sge::renderer::glsl::vertex_shader_ptr const vertex_shader(
		sys.renderer().create_glsl_vertex_shader(
			fcppt::io::stream_to_string(
				vertex_stream
			)
		)
	);

	vertex_shader->compile();

	sge::renderer::glsl::pixel_shader_ptr const pixel_shader(
		sys.renderer().create_glsl_pixel_shader(
			fcppt::io::stream_to_string(
				fragment_stream
			)
		)
	);

	pixel_shader->compile();

	program->vertex_declaration(
		ss.vertex_declaration()
	);

	sge::renderer::glsl::scoped_attachment const vertex_shader_attachment(
		*program,
		*vertex_shader
	);

	sge::renderer::glsl::scoped_attachment const pixel_shader_attachment(
		*program,
		*pixel_shader
	);

	program->link();

	sys.renderer().glsl_program(
		sge::renderer::glsl::const_optional_program(
			*program
		)
	);

	sge::renderer::glsl::uniform::variable_ptr const tex_var(
		program->uniform("tex")
	);

	sge::renderer::glsl::uniform::single_value(
		*tex_var,
		static_cast<int>(0)
	);

	while(
		running
	)
	{
		sys.window_system().poll();
		{
			sys.renderer().glsl_program(
				sge::renderer::glsl::const_optional_program()
			);

			sge::renderer::scoped_target const target_(
				sys.renderer(),
				*target
			);

			sge::renderer::scoped_block const block_(
				sys.renderer()
			);

			typedef std::vector<
				sprite_object
			> sprite_container;

			sprite_container sprites;

			sprites.push_back(bg);
			sprites.push_back(pointer);
			sprites.push_back(tux);

			ss.render(
				sprites.begin(),
				sprites.end(),
				sge::sprite::default_sort(),
				sge::sprite::default_equal()
			);
		}

		sys.renderer().glsl_program(
			sge::renderer::glsl::const_optional_program(
				*program
			)
		);

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		sge::sprite::render_one(
			ss,
			target_spr
		);
	}
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
