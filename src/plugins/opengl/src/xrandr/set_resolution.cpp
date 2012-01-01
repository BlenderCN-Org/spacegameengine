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


#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/set_resolution.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


void
sge::opengl::xrandr::set_resolution(
	awl::backends::x11::window::instance &_window,
	xrandr::configuration_ptr const _config,
	xrandr::mode const &_mode
)
{
	if(
		_mode.rate() != renderer::refresh_rate_dont_care
	)
	{
		if(
			::XRRSetScreenConfigAndRate(
				_window.display().get(),
				_config->get(),
				_window.get(),
				_mode.index(),
				_mode.rotation(),
				static_cast<
					short
				>(
					_mode.rate().get()
				),
				CurrentTime
			) != Success
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("Cannot change screen mode with rate!")
			);
	}
	else
	{
		if(
			::XRRSetScreenConfig(
				_window.display().get(),
				_config->get(),
				_window.get(),
				_mode.index(),
				_mode.rotation(),
				CurrentTime
			) != Success
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("Cannot change screen mode!")
			);
	}
}
