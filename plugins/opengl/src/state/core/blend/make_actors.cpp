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


#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/convert/to_gl_bool.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/core/blend/alpha.hpp>
#include <sge/opengl/state/core/blend/make_actors.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/join.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::core::blend::make_actors(
	sge::opengl::context::object &_context,
	sge::renderer::state::core::blend::parameters const &_parameters
)
{
	return
		fcppt::container::join(
			sge::opengl::state::core::blend::alpha(
				_context,
				_parameters.alpha_variant()
			),
			sge::opengl::state::actor_vector{
				sge::opengl::state::wrap_error_handler<
					sge::opengl::state::actor
				>(
					[
						write_mask = _parameters.write_mask()
					]{
						return
							sge::opengl::call(
								::glColorMask,
								sge::opengl::convert::to_gl_bool(
									write_mask.write_red().get()
								),
								sge::opengl::convert::to_gl_bool(
									write_mask.write_green().get()
								),
								sge::opengl::convert::to_gl_bool(
									write_mask.write_blue().get()
								),
								sge::opengl::convert::to_gl_bool(
									write_mask.write_alpha().get()
								)
							);
					},
					FCPPT_TEXT("glColorMask")
				)
			}
		);
}
