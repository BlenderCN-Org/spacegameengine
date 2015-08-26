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


#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/projection/aspect.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/perspective_af.hpp>
#include <sge/src/renderer/projection/check_near.hpp>
#include <sge/src/renderer/projection/check_near_far.hpp>
#include <fcppt/math/matrix/row.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sge::renderer::matrix4 const
sge::renderer::projection::perspective_af(
	sge::renderer::projection::aspect const _aspect,
	sge::renderer::projection::fov const _fov,
	sge::renderer::projection::near const _near,
	sge::renderer::projection::far const _far
)
{
	sge::renderer::projection::check_near_far(
		_near,
		_far
	);

	sge::renderer::projection::check_near(
		_near
	);

	sge::renderer::scalar const
		far(
			_far.get()
		),
		near(
			_near.get()
		),
		scale_y(
			1.f
			/
			std::tan(
				_fov.get()
				/
				2.f
			)
		),
		scale_x(
			scale_y
			/
			_aspect.get()
		),
		zero(
			0.f
		),
		one(
			1.f
		);

	return
		sge::renderer::matrix4(
			fcppt::math::matrix::row(
				scale_x, zero, zero, zero
			),
			fcppt::math::matrix::row(
				zero, scale_y, zero, zero
			),
			fcppt::math::matrix::row(
				zero, zero, far / (far - near), -near * far / (far - near)
			),
			fcppt::math::matrix::row(
				zero, zero, one, zero
			)
		);
}
