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


/**
 	Example descripton:

	This example demonstrates a simple use case of the stencil buffer.
	Suppose you have a smaller sprite and a bigger sprite.
	The smaller sprite is rendered first and the bigger sprite is
	rendered second. Because the bigger sprite completely overlaps
	the smaller sprite, only the bigger sprite would be visible under
	normal circumstances.
	However, in this example, the stencil buffer is initialized to
	all 0s on each frame. When the smaller sprite is rendered,
	the stencil buffer is incremented to 1 for every pixel that
	the smaller sprite coveres. When the bigger sprite is rendered,
	the stencil test then compares to the reference value 0,
	not touching the area in which the smaller sprite was rendered.
	Thus we create a "hole" in the bigger sprite, leading to the
	same effect as if the two sprites were rendered in reverse order.
*/

#include <sge/config/media_path.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/resource_flags_field.hpp>
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
#include <sge/renderer/state/int.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/stencil_op.hpp>
#include <sge/renderer/state/stencil_op_value.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/process/one.hpp>
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
#include <sge/texture/part_raw.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
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
	// The desired window size.
	sge::window::dim const window_dim(
		1024,
		768
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			// Request a window with the desired size.
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge stencil example")
					),
					window_dim
				)
			)
		)
		(
			// Request a depth and stencil buffer (d24s8).
			// We don't use the depth buffer, but to be most portable,
			// d24s8 is the only sensible choice.
			sge::systems::renderer(
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::d24s8,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::no
					),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				// Put the viewport in the center of the window
				// when the window is bigger than the desired size.
				sge::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			// Request a keyboard collector which acts as if
			// all the connected keyboards were a sinlge keyboard.
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				// Nothing special to do with the cursor.
				sge::systems::cursor_option_field()
			)
		)
		(
			// Request an image loader that can load png files.
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
				)
			)
		)
	);

	// Declare which sprites we want. The sprite should use int as its
	// position and size, and float as its depth, rotation, etc (which we
	// don't use). Also request that the sprite has a normal size (meaning
	// it is a rectangle and consists of two triangles) and that the sprite
	// needs one texture with automatically computed texture coordinates.
	typedef sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				int
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::normal_size,
		boost::mpl::vector1<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_ownership::shared
			>
		>
	> sprite_choices;

	// Declare the sprite buffers type, object type and parameters type.
	typedef sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	> sprite_buffers_type;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	// Allocate a sprite buffers object. This uses dynamic buffers, which
	// means that they are updated every frame.
	sprite_buffers_type sprite_buffers(
		sys.renderer(),
		sge::sprite::buffers::option::dynamic
	);

	// Create the two textures we are going to use
	sge::renderer::texture::planar_scoped_ptr const
		// Create a texture from "grass.png",
		// which uses no mipmapping
		// and clamping at its corners.
		texture_grass(
			sge::renderer::texture::create_planar_from_path(
				sge::config::media_path()
				/ FCPPT_TEXT("images")
				/ FCPPT_TEXT("grass.png"),
				sys.renderer(),
				sys.image_system(),
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null()
			)
		),
		texture_cloudsquare(
			sge::renderer::texture::create_planar_from_path(
				sge::config::media_path()
				/ FCPPT_TEXT("images")
				/ FCPPT_TEXT("cloudsquare.png"),
				sys.renderer(),
				sys.image_system(),
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null()
			)
		);

	// This is our smaller sprite.
	// It will be placed at position (200, 200) and have the size
	// of its texture "grass.png" which is (256, 256).
	sprite_object const small_sprite(
		sprite_parameters()
		.pos(
			sprite_object::vector(
				200,
				200
			)
		)
		.texture(
			// Sprite uses an abstraction of textures
			// (which is texture::part) that can refer to
			// a part of a physical texture.
			// We don't want that here, so we use part_raw which
			// coveres the whole texture.
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				fcppt::ref(
					*texture_grass
				)
			)
		)
		// The sprite will get the texture's size.
		.texture_size()
	);

	// This is our bigger sprite.
	// It will be placed at position (0, 0) and have the size
	// of its texture "cloudsquare.png" which is (512, 512).
	// Everything else is pretty much the same to small_sprite.
	sprite_object const big_sprite(
		sprite_parameters()
		.pos(
			sprite_object::vector::null()
		)
		.texture(
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				fcppt::ref(
					*texture_cloudsquare
				)
			)
		)
		.texture_size()
	);

	// Set running to false when escape is pressed.
	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	while(
		// Process window messages which will also process input.
		sys.window_system().poll()
	)
	{
		// Declare a render block, using the renderer's onscreen target.
		sge::renderer::context::scoped const scoped_block(
			sys.renderer(),
			sys.renderer().onscreen_target()
		);

		// Here, we clear the back buffer with the clear color black() on each frame.
		// We also clear the stencil buffer with value 0.
		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::black()
			)
			.stencil_buffer(
				0
			)
		);

		{
			// Set the stencil buffer to always pass and increment
			// the value stored in the stencil buffer for every pixel rendered.
			// Because the stencil buffer has been cleared to 0,
			// every entry in the stencill buffer will be 1 where
			// small_sprite is rendered.
			sge::renderer::state::scoped const scoped_state(
				scoped_block.get(),
				sge::renderer::state::list
				(
					sge::renderer::state::stencil_func::always
				)
				(
					sge::renderer::state::stencil_op::pass =
						sge::renderer::state::stencil_op_value::inc_sat
				)
			);

			// Render small sprite.
			sge::sprite::process::one(
				scoped_block.get(),
				small_sprite,
				sprite_buffers
			);
		}

		{
			// Set the stencil buffer to pass when its value is still 0,
			// which means it passes everywhere where small_sprite
			// has _not_ been rendered.
			sge::renderer::state::scoped const scoped_state(
				scoped_block.get(),
				sge::renderer::state::list
				(
					sge::renderer::state::int_::stencil_ref = 0
				)
				(
					sge::renderer::state::stencil_func::equal
				)
			);

			// Render big sprite.
			sge::sprite::process::one(
				scoped_block.get(),
				big_sprite,
				sprite_buffers
			);
		}
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
	std::cerr
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}
