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


#ifndef SGE_OPENGL_WINDOWS_STATE_HPP_INCLUDED
#define SGE_OPENGL_WINDOWS_STATE_HPP_INCLUDED

#include <sge/opengl/device_state.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/opengl/wgl/context.hpp>
#include <sge/opengl/wgl/current.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace windows
{

class state
:
	public sge::opengl::device_state
{
	FCPPT_NONCOPYABLE(
		state
	);
public:
	state(
		opengl::context::object &,
		renderer::parameters const &,
		renderer::adapter,
		awl::backends::windows::window::object &
	);

	~state();

	void
	begin_rendering();

	void
	swap_buffers();
private:
	awl::backends::windows::window::object &window_;

	sge::opengl::windows::gdi_device const hdc_;

	wgl::context const context_;

	wgl::current const current_;
};

}
}
}

#endif
