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


#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/egl/context.hpp>
#include <sge/opengl/egl/current.hpp>
#include <sge/opengl/egl/get_display.hpp>
#include <sge/opengl/egl/native_window.hpp>
#include <sge/opengl/egl/native_window_unique_ptr.hpp>
#include <sge/opengl/egl/visual/to_config.hpp>
#include <awl/visual/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::context::context(
	EGLDisplay const _display,
	sge::opengl::egl::native_window_unique_ptr &&_native_window,
	awl::visual::object const &_visual
)
:
	sge::opengl::backend::context(),
	display_(
		_display
	),
	native_window_{
		std::move(
			_native_window
		)
	},
	config_(
		sge::opengl::egl::visual::to_config(
			display_,
			_visual
		)
	),
	surface_(
		_display,
		config_,
		native_window_->get()
	),
	context_(
		_display,
		config_
	)
{
}

sge::opengl::egl::context::~context()
{
}

sge::opengl::backend::current_unique_ptr
sge::opengl::egl::context::activate()
{
	context_.activate(
		surface_.get()
	);

	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::current
		>(
			fcppt::make_unique_ptr<
				sge::opengl::egl::current
			>(
				display_,
				surface_
			)
		);
}

void
sge::opengl::egl::context::deactivate(
	sge::opengl::backend::current_unique_ptr &&
)
{
	context_.deactivate();
}
