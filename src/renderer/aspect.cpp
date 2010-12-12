/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/aspect.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/instantiate_arithmetic.hpp>
#include <fcppt/math/almost_zero.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/export_symbol.hpp>

template<
	typename T
>
T
sge::renderer::aspect(
	screen_size const &_size
)
{
	T const
		w(static_cast<T>(_size.w())),
		h(static_cast<T>(_size.h()));

	FCPPT_ASSERT(
		!fcppt::math::almost_zero(w)
		&& !fcppt::math::almost_zero(h)
	)

	return
		w > h
		?
			w / h
		:
			h / w;
}

#define SGE_INSTANTIATE_ASPECT(x)\
template FCPPT_EXPORT_SYMBOL x sge::renderer::aspect(sge::renderer::screen_size const &);

FCPPT_MATH_INSTANTIATE_ARITHMETIC(SGE_INSTANTIATE_ASPECT)

#undef SGE_INSTANTIATE_ASPECT
