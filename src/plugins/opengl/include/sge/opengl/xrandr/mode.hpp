/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_XRANDR_MODE_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_MODE_HPP_INCLUDED

#include <sge/opengl/xrandr/mode_fwd.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class mode
{
public:
	mode(
		int index,
		Rotation,
		sge::renderer::display_mode::optional_refresh_rate
	);

	int
	index() const;

	Rotation
	rotation() const;

	sge::renderer::display_mode::optional_refresh_rate
	rate() const;
private:
	int const index_;

	Rotation const rotation_;

	sge::renderer::display_mode::optional_refresh_rate const rate_;
};

}
}
}

#endif
