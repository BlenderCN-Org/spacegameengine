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


#ifndef SGE_SRC_CG_PARAMETER_VECTOR_SET_IMPL_HPP_INCLUDED
#define SGE_SRC_CG_PARAMETER_VECTOR_SET_IMPL_HPP_INCLUDED


#include <sge/cg/check_state.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/parameter/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


#define SGE_SRC_CG_PARAMETER_VECTOR_SET_IMPL_CASE(\
	cg_name,\
	count\
)\
case count:\
	::cgSetParameter ## count ## cg_name ## v(\
		_parameter.get(),\
		_data\
	);\
	break\

#define SGE_SRC_CG_PARAMETER_VECTOR_SET_IMPL(\
	type,\
	cg_name\
)\
void \
sge::cg::parameter::vector::detail::set_ ## type(\
	sge::cg::parameter::object const &_parameter,\
	type const *const _data,\
	fcppt::math::size_type const _size\
)\
{\
	switch(\
		_size\
	)\
	{\
	SGE_SRC_CG_PARAMETER_VECTOR_SET_IMPL_CASE(\
		cg_name,\
		1\
	);\
	SGE_SRC_CG_PARAMETER_VECTOR_SET_IMPL_CASE(\
		cg_name,\
		2\
	);\
	SGE_SRC_CG_PARAMETER_VECTOR_SET_IMPL_CASE(\
		cg_name,\
		3\
	);\
	SGE_SRC_CG_PARAMETER_VECTOR_SET_IMPL_CASE(\
		cg_name,\
		4\
	);\
	default:\
		FCPPT_ASSERT_UNREACHABLE;\
	}\
\
	SGE_CG_CHECK_STATE(\
		FCPPT_TEXT("cgSetParameter failed"),\
		sge::cg::exception\
	)\
}

#endif
