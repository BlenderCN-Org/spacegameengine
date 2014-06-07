/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/state/ffp/lighting/light/create.hpp>
#include <sge/d3d9/state/ffp/lighting/light/make_states.hpp>
#include <sge/d3d9/state/ffp/lighting/light/object.hpp>
#include <sge/renderer/state/ffp/lighting/light/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::renderer::state::ffp::lighting::light::object_unique_ptr
sge::d3d9::state::ffp::lighting::light::create(
	IDirect3DDevice9 &_device,
	sge::renderer::state::ffp::lighting::light::parameters const &_parameters
)
{
	return
		sge::renderer::state::ffp::lighting::light::object_unique_ptr(
			fcppt::make_unique_ptr<
				sge::d3d9::state::ffp::lighting::light::object
			>(
				_device,
				sge::d3d9::state::ffp::lighting::light::make_states(
					_parameters
				)
			)
		);
}
