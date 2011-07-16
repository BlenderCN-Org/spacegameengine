/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/scalar.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>

sge::renderer::matrix4 const
sge::renderer::projection::orthogonal(
	projection::rect const &_rect,
	projection::near const _near,
	projection::far const _far
)
{
	renderer::scalar const
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
		renderer::matrix4(
			2.f / (right - left), zero, zero, zero,
			zero, 2.f / (top - bottom), zero, zero,
			zero, zero, 1.f / (far - near), zero,
			(left + right) / (left - right), (top + bottom) / (bottom - top), near / (near - far), one
		);
}
