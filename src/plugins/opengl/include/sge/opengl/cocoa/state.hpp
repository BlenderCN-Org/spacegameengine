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


#ifndef SGE_OPENGL_COCOA_STATE_HPP_INCLUDED
#define SGE_OPENGL_COCOA_STATE_HPP_INCLUDED

#include <awl/backends/cocoa/window/instance_fwd.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/device_state.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>

@class SGECocoaOpenGLView;

namespace sge
{
namespace opengl
{
namespace cocoa
{
class state
:
	public opengl::device_state
{
FCPPT_NONCOPYABLE(
	state);
public:
	explicit
	state(
		opengl::context::object &,
		renderer::parameters const &,
		renderer::adapter,
		awl::backends::cocoa::window::instance &);

	~state();

	void
	begin_rendering();

	void
	swap_buffers();
private:
	SGECocoaOpenGLView *opengl_view_;
};
}
}
}

#endif