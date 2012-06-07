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


#include <sge/opengl/config.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/device_state/create.hpp>
#include <sge/opengl/device_state/object_unique_ptr.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <fcppt/config/platform.hpp>
#if defined(SGE_OPENGL_HAVE_X11)
#include <sge/opengl/x11/state.hpp>
#include <awl/backends/x11/window/object.hpp>
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/opengl/windows/state.hpp>
#include <awl/backends/windows/window/object.hpp>
#elif defined(FCPPT_CONFIG_DARWIN_PLATFORM)
#include <sge/opengl/cocoa/create_device_state.hpp>
#include <sge/opengl/device_state.hpp>
#else
#error "Implement me!"
#endif
#include <awl/window/object.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>


sge::opengl::device_state::object_unique_ptr
sge::opengl::device_state::create(
	sge::opengl::context::system::object &_context,
	sge::renderer::parameters const &_parameters,
	awl::window::object &_window
)
{
#if defined(SGE_OPENGL_HAVE_X11)
	return
		sge::opengl::device_state::object_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::x11::state
			>(
				fcppt::ref(
					_context
				),
				fcppt::cref(
					_parameters
				),
				fcppt::ref(
					dynamic_cast<
						awl::backends::x11::window::object &
					>(
						_window
					)
				)
			)
		);
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	return
		sge::opengl::device_state::object_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::windows::state
			>(
				fcppt::ref(
					_context
				),
				fcppt::cref(
					_parameters
				),
				fcppt::ref(
					dynamic_cast<
						awl::backends::windows::window::object &
					>(
						_window
					)
				)
			)
		);
#elif defined(FCPPT_CONFIG_DARWIN_PLATFORM)
	return
		sge::opengl::cocoa::create_device_state(
			_context,
			_parameters,
			_window
		);
#else
#error "Implement me!"
#endif
}