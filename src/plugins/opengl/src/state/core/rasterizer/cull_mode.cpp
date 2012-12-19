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


#include <sge/opengl/common.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/cull_mode.hpp>
#include <sge/opengl/state/core/rasterizer/cull_mode.hpp>
#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/phoenix/bind.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor_vector const
sge::opengl::state::core::rasterizer::cull_mode(
	sge::renderer::state::core::rasterizer::cull_mode::type const _mode
)
{
	return
		_mode
		==
		sge::renderer::state::core::rasterizer::cull_mode::off
		?
			fcppt::assign::make_container<
				sge::opengl::state::actor_vector
			>(
				std::bind(
					sge::opengl::disable,
					GL_CULL_FACE
				)
			)
		:
			fcppt::assign::make_container<
				sge::opengl::state::actor_vector
			>(
				std::bind(
					sge::opengl::enable,
					GL_CULL_FACE
				)
			)(
				sge::opengl::state::wrap_error_handler<
					sge::opengl::state::actor
				>(
					boost::phoenix::bind(
						::glCullFace,
						sge::opengl::state::convert::cull_mode(
							_mode
						)
					),
					FCPPT_TEXT("glCullFace")
				)
			);
}
