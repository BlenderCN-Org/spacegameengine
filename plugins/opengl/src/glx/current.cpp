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


#include <sge/opengl/common.hpp>
#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/glx/current.hpp>
#include <sge/opengl/glx/optional_proc_address_function.hpp>
#include <sge/opengl/glx/proc_address_function_ref.hpp>
#include <sge/opengl/glx/swap_functions.hpp>
#include <sge/opengl/glx/vsync.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <string>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::current::current(
	fcppt::log::object &_log,
	awl::backends::x11::window::object &_window,
	sge::opengl::glx::optional_proc_address_function const &_opt_proc_address
)
:
	sge::opengl::backend::current(),
	log_{
		_log
	},
	window_(
		_window
	),
	proc_address_(
		_opt_proc_address
	),
	swap_functions_(
		fcppt::optional::map(
			_opt_proc_address,
			[](
				sge::opengl::glx::proc_address_function_ref const _proc_address
			)
			{
				return
					sge::opengl::glx::swap_functions(
						_proc_address.get()
					);
			}
		)
	)
{
}

sge::opengl::glx::current::~current()
{
}


void
sge::opengl::glx::current::begin_rendering()
{
}

sge::opengl::backend::fun_ptr
sge::opengl::glx::current::load_function(
	std::string const &_name
) const
{
	// TODO: Use optionals
	return
		fcppt::optional::maybe(
			proc_address_,
			[]{
				return
					sge::opengl::backend::fun_ptr(
						nullptr
					);
			},
			[
				&_name
			](
				sge::opengl::glx::proc_address_function_ref const _proc_address
			)
			{
				return
					_proc_address.get()(
						fcppt::cast::to_char_ptr<
							GLubyte const *
						>(
							_name.c_str()
						)
					);
			}
		);
}

void
sge::opengl::glx::current::end_rendering()
{
	if(
		!window_.destroyed()
	)
		::glXSwapBuffers(
			window_.display().get(),
			window_.get()
		);
}
void
sge::opengl::glx::current::vsync(
	sge::renderer::display_mode::vsync const _vsync
)
{
	if(
		_vsync
		==
		sge::renderer::display_mode::vsync::on
	)
		fcppt::optional::maybe(
			swap_functions_,
			[
				this
			]{
				FCPPT_LOG_ERROR(
					log_,
					fcppt::log::out
						<<
						FCPPT_TEXT("GLX extensions not available.")
						FCPPT_TEXT(" Setting vsync is not supported.")

				)
			},
			[
				this
			](
				sge::opengl::glx::swap_functions const &_swap_functions
			)
			{
				sge::opengl::glx::vsync(
					log_,
					_swap_functions,
					window_.display()
				);
			}
		);
}
