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


#include <sge/config/media_path.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/muxing_narrow_streambuf.hpp>
#include <sge/console/object.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/console/sprite_parameters.hpp>
#include <sge/console/callback/from_functor.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/metrics_scoped_ptr.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/text/to_fcppt_string.hpp>
#include <sge/image/colors.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/windowed.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/insert_to_string.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace
{
void
fallback(
	sge::font::text::string const &_arg
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("fallback called with argument:")
		<< sge::font::text::to_fcppt_string(
			_arg
		)
		<< FCPPT_TEXT('\n');
}

void
quit(
	sge::window::system &_window_system
)
{
	_window_system.quit(
		awl::main::exit_success()
	);
}

void
increment(
	sge::console::object &_console,
	float const f)
{
	_console.emit_message(
		SGE_FONT_TEXT_LIT("New value is ")+
		fcppt::insert_to_string<sge::font::text::string>(
			f+1.0f));
}

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
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
						FCPPT_TEXT("sge console test")
					),
					window_dim
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::windowed(
						sge::renderer::bit_depth::depth32
					),
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
				),
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::font()
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
				)
			)
		)
	);

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	sge::console::object object(
		SGE_FONT_TEXT_LIT('/')
	);

	fcppt::signal::scoped_connection const c0(
		object.insert(
			sge::console::callback::from_functor<void()>(
				std::tr1::bind(
					&quit,
					fcppt::ref(
						sys.window_system())),
				sge::console::callback::name(
					SGE_FONT_TEXT_LIT("quit")),
				sge::console::callback::short_description(
					SGE_FONT_TEXT_LIT("Usage: /quit")))));

	fcppt::signal::scoped_connection const c1(
		object.register_fallback(
			&fallback
		)
	);

	fcppt::signal::scoped_connection const c2(
		object.insert(
			sge::console::callback::from_functor<void(float)>(
				std::tr1::bind(
					&increment,
					fcppt::ref(
						object),
					std::tr1::placeholders::_1),
				sge::console::callback::name(
					SGE_FONT_TEXT_LIT("increment")),
				sge::console::callback::short_description(
					SGE_FONT_TEXT_LIT("Usage: /increment <float-value>")))
				.long_description(
					SGE_FONT_TEXT_LIT("Increments the float value (extremely useful!)"))));

	sge::texture::manager tex_man(
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>
		(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>
			(
				fcppt::ref(
					sys.renderer()
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off()
			)
		)
	);

	sge::texture::const_part_shared_ptr const
		tex_bg(
			sge::texture::add_image(
				tex_man,
				*sys.image_system().load(
					sge::config::media_path()
					/ FCPPT_TEXT("images")
					/ FCPPT_TEXT("grass.png")
				)
			)
		);

	sge::font::metrics_scoped_ptr const font_metrics(
		sys.font_system().create_font(
			sge::config::media_path()
			/ FCPPT_TEXT("fonts")
			/ FCPPT_TEXT("default.ttf"),
			15
		)
	);

	sge::console::gfx gfx_(
		object,
		sys.renderer(),
		sge::image::colors::white(),
		*font_metrics,
		sys.keyboard_collector(),
		sge::console::sprite_object(
			sge::console::sprite_parameters()
			.pos(
				sge::console::sprite_object::vector::null()
			)
			.texture(
				tex_bg
			)
			.size(
				sge::console::sprite_object::dim(400,300)
			)
		),
		static_cast<
			sge::console::output_line_limit
		>(
			100
		)
	);

	sge::console::muxing_narrow_streambuf stdout_streambuf(
		std::cout,
		object,
		sge::console::muxing::enabled);

	std::cout << "Test for console muxer (cout).\n";
	std::cout << "You should see this message in the console and in the terminal (if available)\n";

	sge::console::muxing_narrow_streambuf stderr_streambuf(
		std::cerr,
		object,
		sge::console::muxing::disabled);

	std::cerr << "Test for console muxer (cerr).\n";
	std::cerr << "You should see this message _only_ in the console and _not_ in the terminal (if available)\n";

	gfx_.active(
		true
	);

	while(
		sys.window_system().poll()
	)
	{
		sys.renderer().onscreen_target().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::black()
			)
		);

		sge::renderer::scoped_block const block(
			sys.renderer()
		);

		gfx_.render();
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
