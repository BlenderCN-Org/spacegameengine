/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <fcppt/assert/post.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::configuration::configuration(
	awl::backends::x11::window::base const &_window
)
:
	config_{
		::XRRGetScreenInfo(
			_window.display().get(),
			_window.get()
		)
	}
{
	FCPPT_ASSERT_POST(
		config_
		!=
		nullptr,
		sge::renderer::exception
	);
}

::XRRScreenConfiguration *
sge::opengl::xrandr::configuration::get() const
{
	return
		config_;
}

sge::opengl::xrandr::configuration::~configuration()
{
	::XRRFreeScreenConfigInfo(
		config_
	);
}
