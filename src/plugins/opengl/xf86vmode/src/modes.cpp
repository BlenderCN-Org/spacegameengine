/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../modes.hpp"
#include <sge/x11/display.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::xf86vmode::modes::modes(
	x11::display_ptr const dsp,
	int const screen_)
:
	dsp(dsp),
	screen_(screen_)
{
	{
		int event_base, error_base;
		if(XF86VidModeQueryExtension(
			dsp->get(),
			&event_base,
			&error_base)
		== False)
			throw exception(
				SGE_TEXT("xf86vmode video modes queried but extension is not present!"));
	}

	int mode_count;
	XF86VidModeModeInfo **ret;
	if(XF86VidModeGetAllModeLines(
		dsp->get(),
		screen(),
		&mode_count,
		&ret)
	== False)
		throw exception(
			SGE_TEXT("XF86VidModeGetAllModeLines() failed"));
	modes_.reset(ret);
	sz = mode_count >= 0 ? mode_count : 0;
}

XF86VidModeModeInfo const &
sge::ogl::xf86vmode::modes::operator[](
	size_type const index) const
{
	return (*modes_)[index];
}

sge::ogl::xf86vmode::modes::size_type
sge::ogl::xf86vmode::modes::size() const
{
	return sz;
}

sge::x11::display_ptr const
sge::ogl::xf86vmode::modes::display() const
{
	return dsp;
}

int sge::ogl::xf86vmode::modes::screen() const
{
	return screen_;
}
