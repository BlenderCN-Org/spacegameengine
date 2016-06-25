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


#include <sge/input/exception.hpp>
#include <sge/x11input/color.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::color::color(
	awl::backends::x11::display &_display,
	Colormap const _colormap,
	fcppt::string const &_name
)
:
	display_(
		_display
	),
	colormap_(
		_colormap
	),
	color_(
		[
			this,
			&_name
		]{
			XColor dummy;

			XColor result;

			if(
				::XAllocNamedColor(
					display_.get(),
					colormap_,
					fcppt::to_std_string(
						_name
					).c_str(),
					&result,
					&dummy
				)
				== 0
			)
				throw
					sge::input::exception{
						FCPPT_TEXT("XAllocNamedColor() failed!")
					};

			return
				result;
		}()
	)
{
}

sge::x11input::color::~color()
{
	::XFreeColors(
		display_.get(),
		colormap_,
		&color_.pixel,
		1,
		0
	);
}

XColor
sge::x11input::color::get() const
{
	return
		color_;
}
