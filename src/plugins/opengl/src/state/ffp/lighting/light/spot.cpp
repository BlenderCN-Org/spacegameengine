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


#include <sge/opengl/state/index_actor_vector.hpp>
#include <sge/opengl/state/ffp/lighting/light/attenuation.hpp>
#include <sge/opengl/state/ffp/lighting/light/cutoff_angle.hpp>
#include <sge/opengl/state/ffp/lighting/light/direction.hpp>
#include <sge/opengl/state/ffp/lighting/light/position.hpp>
#include <sge/opengl/state/ffp/lighting/light/spot.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/assign/make_container.hpp>


sge::opengl::state::index_actor_vector const
sge::opengl::state::ffp::lighting::light::spot(
	sge::renderer::state::ffp::lighting::light::spot const &_spot
)
{
	return
		fcppt::algorithm::join(
			fcppt::assign::make_container<
				sge::opengl::state::index_actor_vector
			>(
				sge::opengl::state::ffp::lighting::light::position(
					_spot.position()
				)
			)(
				sge::opengl::state::ffp::lighting::light::direction(
					_spot.direction()
				)
			)(
				sge::opengl::state::ffp::lighting::light::cutoff_angle(
					_spot.cutoff_angle()
				)
			)
			.container(),
			sge::opengl::state::ffp::lighting::light::attenuation(
				_spot.attenuation()
			)
		);
}