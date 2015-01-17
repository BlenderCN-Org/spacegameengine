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


#ifndef SGE_OPENGL_GLX_VISUAL_CHOOSE_HPP_INCLUDED
#define SGE_OPENGL_GLX_VISUAL_CHOOSE_HPP_INCLUDED

#include <sge/opengl/glx/visual/attribute_container.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/screen.hpp>
#include <awl/backends/x11/visual/info_unique_ptr.hpp>


namespace sge
{
namespace opengl
{
namespace glx
{
namespace visual
{

awl::backends::x11::visual::info_unique_ptr
choose(
	awl::backends::x11::display const &,
	awl::backends::x11::screen,
	sge::opengl::glx::visual::attribute_container const &
);

}
}
}
}

#endif
