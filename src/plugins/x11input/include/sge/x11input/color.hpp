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


#ifndef SGE_X11INPUT_COLOR_HPP_INCLUDED
#define SGE_X11INPUT_COLOR_HPP_INCLUDED

#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{

class color
{
	FCPPT_NONCOPYABLE(
		color
	);
public:
	color(
		awl::backends::x11::display &,
		Colormap,
		fcppt::string const &name
	);

	~color();

	XColor
	get() const;
private:
	awl::backends::x11::display &display_;

	Colormap const colormap_;

	XColor color_;
};

}
}

#endif
