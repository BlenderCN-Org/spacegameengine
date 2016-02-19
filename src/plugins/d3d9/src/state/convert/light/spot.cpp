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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/light/attenuation.hpp>
#include <sge/d3d9/state/convert/light/cutoff_angle.hpp>
#include <sge/d3d9/state/convert/light/direction.hpp>
#include <sge/d3d9/state/convert/light/position.hpp>
#include <sge/d3d9/state/convert/light/spot.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot.hpp>


void
sge::d3d9::state::convert::light::spot(
	D3DLIGHT9 &_light,
	sge::renderer::state::ffp::lighting::light::spot const &_spot
)
{
	_light.Type = D3DLIGHT_SPOT;

	sge::d3d9::state::convert::light::attenuation(
		_light,
		_spot.attenuation()
	);

	sge::d3d9::state::convert::light::cutoff_angle(
		_light,
		_spot.cutoff_angle()
	);

	sge::d3d9::state::convert::light::direction(
		_light,
		_spot.direction()
	);

	sge::d3d9::state::convert::light::position(
		_light,
		_spot.position()
	);
}
