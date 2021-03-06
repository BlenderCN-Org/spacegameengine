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


#include <sge/opengl/egl/visual/base.hpp>
#include <sge/opengl/egl/visual/choose_config.hpp>
#include <sge/opengl/egl/visual/make_attributes.hpp>
#include <sge/renderer/visual_base.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::visual::base::base(
	fcppt::log::object &_log,
	EGLDisplay const _egl_display,
	sge::renderer::pixel_format::object const &_pixel_format
)
:
	sge::renderer::visual_base(
		_pixel_format
	),
	config_(
		sge::opengl::egl::visual::choose_config(
			_log,
			_egl_display,
			sge::opengl::egl::visual::make_attributes(
				_pixel_format
			)
		)
	)
{
}

sge::opengl::egl::visual::base::~base()
{
}

EGLConfig
sge::opengl::egl::visual::base::config() const
{
	return
		config_;
}
