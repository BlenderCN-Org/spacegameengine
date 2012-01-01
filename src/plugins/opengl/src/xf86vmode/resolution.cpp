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


#include <sge/opengl/xf86vmode/resolution.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>


sge::opengl::xf86vmode::resolution::resolution(
	awl::backends::x11::display &_display,
	awl::backends::x11::screen const _screen,
	XF86VidModeModeInfo const &_new_mode,
	XF86VidModeModeInfo const &_old_mode
)
:
	display_(_display),
	screen_(_screen),
	old_mode_(_old_mode)
{
	if(
		::XF86VidModeSwitchToMode(
			display_.get(),
			screen_.get(),
			const_cast<
				::XF86VidModeModeInfo *
			>(
				&_new_mode
			)
		)
		== False
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("XF86VidModeSwitchToMode() failed!")
		);

	::XF86VidModeSetViewPort(
		display_.get(),
		screen_.get(),
		0,
		0
	);
}

sge::opengl::xf86vmode::resolution::~resolution()
{
	::XF86VidModeSwitchToMode(
		display_.get(),
		screen_.get(),
		const_cast<
			::XF86VidModeModeInfo *
		>(
			&old_mode_
		)
	);
}
