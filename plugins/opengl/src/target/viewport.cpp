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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/target/set_flipped_area.hpp>
#include <sge/opengl/target/viewport.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::target::viewport(
	sge::renderer::target::viewport const &_viewport,
	sge::renderer::screen_unit const _height
)
{
	sge::opengl::target::set_flipped_area(
		::glViewport,
		_viewport.get(),
		_height
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glViewport failed"),
		sge::renderer::exception
	)
}
