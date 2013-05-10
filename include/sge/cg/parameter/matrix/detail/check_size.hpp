/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CG_PARAMETER_MATRIX_DETAIL_CHECK_SIZE_HPP_INCLUDED
#define SGE_CG_PARAMETER_MATRIX_DETAIL_CHECK_SIZE_HPP_INCLUDED

#include <sge/cg/symbol.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <fcppt/math/matrix/dim_fwd.hpp>


namespace sge
{
namespace cg
{
namespace parameter
{
namespace matrix
{
namespace detail
{

SGE_CG_SYMBOL
void
check_size(
	sge::cg::parameter::object const &,
	fcppt::math::matrix::dim const &
);

}
}
}
}
}

#endif
