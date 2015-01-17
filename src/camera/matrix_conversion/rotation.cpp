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


#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/matrix_conversion/rotation.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/vector3.hpp>


sge::renderer::matrix4 const
sge::camera::matrix_conversion::rotation(
	camera::coordinate_system::object const &_coordinate_system)
{
	sge::renderer::vector3 const
		r(
			_coordinate_system.right().get()),
		u(
			_coordinate_system.up().get()),
		f(
			_coordinate_system.forward().get());

	return
		sge::renderer::matrix4(
			r[0],r[1],r[2],0.0f,
			u[0],u[1],u[2],0.0f,
			f[0],f[1],f[2],0.0f,
			0.0f,0.0f,0.0f,1.0f);
}
