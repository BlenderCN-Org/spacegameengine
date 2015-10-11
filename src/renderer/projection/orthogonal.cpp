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
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <sge/src/renderer/projection/check_near_far.hpp>
#include <fcppt/math/matrix/row.hpp>


sge::renderer::matrix4
sge::renderer::projection::orthogonal(
	sge::renderer::projection::rect const &_rect,
	sge::renderer::projection::near const _near,
	sge::renderer::projection::far const _far
)
{
	sge::renderer::projection::check_near_far(
		_near,
		_far
	);

	sge::renderer::scalar const
		one(
			1.f
		),
		zero(
			0.f
		),
		left(
			_rect.left()
		),
		right(
			_rect.right()
		),
		top(
			_rect.top()
		),
		bottom(
			_rect.bottom()
		),
		near(
			_near.get()
		),
		far(
			_far.get()
		);

	return
		sge::renderer::matrix4(
			fcppt::math::matrix::row(
				2.f / (right - left), zero, zero, (left + right) / (left - right)
			),
			fcppt::math::matrix::row(
				zero, 2.f / (top - bottom), zero, (top + bottom) / (bottom - top)
			),
			fcppt::math::matrix::row(
				zero, zero, 1.f / (far - near), near / (near - far)
			),
			fcppt::math::matrix::row(
				zero, zero, zero, one
			)
		);
}
