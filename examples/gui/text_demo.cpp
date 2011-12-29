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


#include <sge/cegui/cursor_visibility.hpp>
#include <sge/cegui/default_cursor.hpp>
#include <sge/cegui/default_keyboard.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/cegui/system.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/cegui/toolbox/scoped_gui_sheet.hpp>
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/log/global.hpp>
#include <sge/log/global_context.hpp>
#include <sge/log/location.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/systems/charconv.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/chrono/duration.hpp>
#include <fcppt/chrono/duration_cast.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <elements/CEGUIEditbox.h>
#include <elements/CEGUIFrameWindow.h>
#include <CEGUIWindowManager.h>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <set>
#include <fcppt/config/external_end.hpp>


int main(
	int,
	char *[])
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	// Usually too verbose (maybe add a log switcher later?)
	sge::log::global_context().apply(
		fcppt::log::location(
			sge::log::location()
			/
			FCPPT_TEXT("cegui")),
		std::tr1::bind(
			&fcppt::log::object::activate,
			std::tr1::placeholders::_1,
			fcppt::log::level::debug));

	sge::systems::instance const sys(
		sge::systems::list()
		(sge::systems::window(
			sge::window::parameters(
				sge::window::title(
					FCPPT_TEXT("simple gui test")),
				sge::window::dim(1024,768))))
		(sge::systems::renderer(
			sge::renderer::parameters(
				sge::renderer::visual_depth::depth32,
				sge::renderer::depth_stencil_buffer::d24,
				sge::renderer::vsync::on,
				sge::renderer::no_multi_sampling),
			sge::viewport::fill_on_resize()))
		(sge::systems::charconv())
			(sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<sge::media::extension_set>(
						sge::media::extension(
							FCPPT_TEXT("png"))))))
		(sge::systems::input(
			sge::systems::input_helper_field(
				sge::systems::input_helper::keyboard_collector) | sge::systems::input_helper::mouse_collector | sge::systems::input_helper::cursor_demuxer,
			sge::systems::cursor_option_field())));

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running))));

	sge::cegui::system gui_sys(
		sge::cegui::load_context(
			sge::config::media_path()/FCPPT_TEXT("gui")/FCPPT_TEXT("TaharezLook.scheme"))
			.font_directory(
				sge::config::media_path()/FCPPT_TEXT("fonts")),
		sys.renderer(),
		sys.image_system(),
		sys.charconv_system(),
		sys.viewport_manager(),
		sge::cegui::cursor_visibility::visible);

	sge::cegui::syringe gui_syringe(
		gui_sys);

	sge::cegui::default_cursor gui_cursor(
		gui_syringe,
		sys.cursor_demuxer());

	sge::cegui::default_keyboard gui_keyboard(
		gui_syringe,
		sys.keyboard_collector());

	sge::timer::basic<sge::timer::clocks::standard> frame_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			sge::cegui::duration(
				static_cast<sge::cegui::unit>(
					1))));

	sge::cegui::toolbox::scoped_layout scoped_layout(
		gui_sys,
		sge::config::media_path()/FCPPT_TEXT("gui")/FCPPT_TEXT("text_demo.layout"),
		sys.charconv_system());

	sge::cegui::toolbox::scoped_gui_sheet const scoped_gui_sheet(
		gui_sys,
		scoped_layout.window()
	);

	while (running)
	{
		sys.window_system().poll();

		gui_sys.update(
			sge::timer::elapsed<sge::cegui::duration>(
				frame_timer));

		frame_timer.reset();

		sge::renderer::state::scoped scoped_state(
			sys.renderer(),
			sge::renderer::state::list
				(sge::renderer::state::bool_::clear_back_buffer = true)
				(sge::renderer::state::color::back_buffer_clear_color = sge::image::colors::red()));

		sge::renderer::scoped_block scoped_block(
			sys.renderer());

		gui_sys.render();
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
