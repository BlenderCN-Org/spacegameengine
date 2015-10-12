/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/coordinate_system/object_fwd.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/matrix_conversion/world_projection.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>


sge::renderer::matrix4
sge::camera::matrix_conversion::world_projection(
	sge::camera::coordinate_system::object const &_coordinate_system,
	sge::camera::projection_matrix const &_projection
)
{
	return
		_projection.get()
		*
		sge::camera::matrix_conversion::world(
			_coordinate_system
		);
}
