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
#include <sge/opengl/egl/surface.hpp>
#include <sge/opengl/egl/surface_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::context::context(
	EGLDisplay const _display,
	EGLConfig const _config,
	sge::opengl::egl::surface_unique_ptr &&_surface
)
:
	sge::opengl::backend::context(),
	display_{
		_display
	},
	surface_{
		std::move(
			_surface
		)
	},
	context_{
		_display,
		_config
	}
{
}

sge::opengl::egl::context::~context()
{
}

sge::opengl::backend::current_unique_ptr
sge::opengl::egl::context::activate()
{
	context_.activate(
		surface_->get()
	);

	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::current
		>(
			fcppt::make_unique_ptr<
				sge::opengl::egl::current
			>(
				display_,
				surface_->get()
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
