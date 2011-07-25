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


#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/viewport/dont_manage.hpp>
#include <sge/window/instance.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/image/colors.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/chrono/seconds.hpp>
#include <fcppt/text.hpp>
#include <ostream>
#include <exception>
#include <cstdlib>

int main()
try
{
	sge::window::dim const window_dim(
		800,
		600
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge fullscreen test"),
					window_dim
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::display_mode(
						fcppt::math::dim::structure_cast<
							sge::renderer::screen_size
						>(
							window_dim
						),
						sge::renderer::bit_depth::depth32,
						sge::renderer::refresh_rate_dont_care
					),
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::viewport::dont_manage()
			)
		)
	);

	sge::timer::clocks::standard global_clock;

	sge::timer::basic<sge::timer::clocks::standard> tm(
		sge::timer::parameters<sge::timer::clocks::standard>(
			global_clock,
			fcppt::chrono::seconds(
				5)));

	sge::renderer::device &rend(
		sys.renderer()
	);

	rend.state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(sge::renderer::state::color::back_buffer_clear_color
				= sge::image::colors::yellow()
			)
	);

	while(
		!tm.expired())
	{
		sys.window().dispatch();

		sge::renderer::scoped_block const block_(rend);
	}
}
catch(
	sge::exception const &_error
)
{
	fcppt::io::cerr
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	fcppt::io::cerr
		<< _error.what()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
