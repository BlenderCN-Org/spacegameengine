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
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/alpha_func.hpp>
#include <sge/opengl/state/ffp/alpha_test/make_actors.hpp>
#include <sge/renderer/state/ffp/alpha_test/enabled.hpp>
#include <sge/renderer/state/ffp/alpha_test/off_fwd.hpp>
#include <sge/renderer/state/ffp/alpha_test/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/match.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::ffp::alpha_test::make_actors(
	sge::renderer::state::ffp::alpha_test::parameters const &_parameters
)
{
	return
		fcppt::variant::match(
			_parameters.variant(),
			[](
				sge::renderer::state::ffp::alpha_test::off const &
			)
			{
				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::actor{
							[]{
								return
									sge::opengl::disable(
										GL_ALPHA_TEST
									);
							}
						}
					};
			},
			[](
				sge::renderer::state::ffp::alpha_test::enabled const &_enabled
			)
			{
				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::actor{
							[]{
								return
									sge::opengl::enable(
										GL_ALPHA_TEST
									);
							}
						},
						sge::opengl::state::wrap_error_handler<
							sge::opengl::state::actor
						>(
							[
								_enabled
							]{
								return
									sge::opengl::call(
										::glAlphaFunc,
										sge::opengl::state::convert::alpha_func(
											_enabled.func()
										),
										_enabled.ref().get()
									);
							},
							FCPPT_TEXT("glAlphaFunc")
						)
					};
			}
		);
}
