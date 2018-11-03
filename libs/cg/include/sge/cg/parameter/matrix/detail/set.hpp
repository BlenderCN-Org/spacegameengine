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


#ifndef SGE_CG_PARAMETER_MATRIX_DETAIL_SET_HPP_INCLUDED
#define SGE_CG_PARAMETER_MATRIX_DETAIL_SET_HPP_INCLUDED

#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/detail/pp_types.hpp>
#include <sge/cg/parameter/matrix/detail/set_double.hpp>
#include <sge/cg/parameter/matrix/detail/set_float.hpp>
#include <sge/cg/parameter/matrix/detail/set_int.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


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

#define SGE_CG_PARAMETER_MATRIX_DETAIL_SET(\
	seq,\
	_,\
	type\
)\
template<\
	fcppt::math::size_type R,\
	fcppt::math::size_type C,\
	typename S\
>\
void \
set(\
	sge::cg::parameter::object const &_parameter,\
	fcppt::math::matrix::object<\
		type,\
		R,\
		C,\
		S\
	> const &_matrix\
)\
{\
	sge::cg::parameter::matrix::detail:: BOOST_PP_CAT(set_, type)(\
		_parameter,\
		_matrix.storage().data()\
	);\
}

BOOST_PP_SEQ_FOR_EACH(
	SGE_CG_PARAMETER_MATRIX_DETAIL_SET,
	_,
	SGE_CG_PARAMETER_DETAIL_PP_TYPES
)

}
}
}
}
}

#endif
