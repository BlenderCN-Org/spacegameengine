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
#include <sge/d3d9/state/convert/light/directional.hpp>
#include <sge/d3d9/state/convert/light/point.hpp>
#include <sge/d3d9/state/convert/light/spot.hpp>
#include <sge/d3d9/state/convert/light/visitor.hpp>
#include <sge/renderer/state/ffp/lighting/light/directional_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/point_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot_fwd.hpp>


sge::d3d9::state::convert::light::visitor::visitor(
	D3DLIGHT9 &_object
)
:
	object_(
		_object
	)
{
}

sge::d3d9::state::convert::light::visitor::result_type
sge::d3d9::state::convert::light::visitor::operator()(
	sge::renderer::state::ffp::lighting::light::directional const &_directional
) const
{
	sge::d3d9::state::convert::light::directional(
		object_,
		_directional
	);
}

sge::d3d9::state::convert::light::visitor::result_type
sge::d3d9::state::convert::light::visitor::operator()(
	sge::renderer::state::ffp::lighting::light::point const &_point
) const
{
	sge::d3d9::state::convert::light::point(
		object_,
		_point
	);
}

sge::d3d9::state::convert::light::visitor::result_type
sge::d3d9::state::convert::light::visitor::operator()(
	sge::renderer::state::ffp::lighting::light::spot const &_spot
) const
{
	sge::d3d9::state::convert::light::spot(
		object_,
		_spot
	);
}
