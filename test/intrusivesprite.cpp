/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/image/multi_loader.hpp>
#include <sge/image/color/format.hpp>
#include <sge/input/system.hpp>
#include <sge/input/action.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/with_repetition.hpp>
#include <sge/sprite/with_rotation.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/sprite/intrusive/tag.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/window/parameters.hpp>
#include <sge/exception.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <exception>
#include <ostream>
#include <cstdlib>

int main()
try
{
	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::window::parameters(
				FCPPT_TEXT("sge intrusive sprite test")
			)
		)
		(
			sge::renderer::parameters(
				sge::renderer::display_mode(
					sge::renderer::screen_size(
						1024,
						768
					),
					sge::renderer::bit_depth::depth32,
					sge::renderer::refresh_rate_dont_care
				),
				sge::renderer::depth_buffer::off,
				sge::renderer::stencil_buffer::off,
				sge::renderer::window_mode::windowed,
				sge::renderer::vsync::on,
				sge::renderer::no_multi_sampling
			)
		)
		(
			sge::systems::parameterless::input
		)
		(
			sge::systems::parameterless::image
		)
	);

	sge::image::multi_loader image_loader(
		sys.plugin_manager()
	);

	typedef sge::texture::default_creator<
		sge::texture::no_fragmented
	> texture_creator;
	
	texture_creator const creator(
		sys.renderer(),
		sge::image::color::format::rgba8,
		sge::renderer::filter::linear
	);

	sge::texture::manager tex_man(
		sys.renderer(),
		creator
	);

	sge::texture::const_part_ptr const
		tex1(
			sge::texture::add_image(
				tex_man,
				image_loader.load(
					sge::config::media_path()
					/ FCPPT_TEXT("cloudsquare.jpg")
				)
			)
		),
		tex2(
			sge::texture::add_image(
				tex_man,
				image_loader.load(
					sge::config::media_path()
					/ FCPPT_TEXT("grass.png")
				)
			)
		);


	typedef sge::sprite::choices<
		sge::sprite::type_choices<
			int,
			float,
			sge::sprite::no_color
		>,
		boost::mpl::vector4<
			sge::sprite::with_texture,
			sge::sprite::with_rotation,
			sge::sprite::with_repetition,
			sge::sprite::intrusive::tag
		>
	> sprite_choices;

	typedef sge::sprite::system<
		sprite_choices
	>::type sprite_system;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_system system(
		sys.renderer()
	);

	sprite_object test(
		sprite_parameters()
		.pos(
			sprite_object::point::null()
		)
		.texture(
			tex1
		)
		.texture_size()
		.order(
			3u
		)
		.rotation(
			1.5f
		)
		.system(
			&system
		)
		.repetition(
			2.f
		)
		.elements()
	);

	sprite_object test2;

	test2 = test;

	test2.pos(
		sprite_object::point(
			400,
			50
		)
	);

	test2.rotation(
		-0.5f
	);

	test2.order(
		2u
	);

	test2.texture(
		tex2
	);
	
	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.input_system()->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	while(running)
	{
		sge::mainloop::dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		system.render_all(
			sge::sprite::default_equal()
		);
	}

}
catch(
	sge::exception const &e
)
{
	sge::cerr
		<< e.string()
		<< FCPPT_TEXT('\n');
	
	return EXIT_FAILURE;
}
catch(
	std::exception const &e
)
{
	sge::cerr
		<< e.what()
		<< FCPPT_TEXT('\n');
	
	return EXIT_FAILURE;
}
