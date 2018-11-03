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


#include <sge/cg/impl/parameter/get_type.hpp>
#include <sge/cg/impl/parameter/type_base_enum.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/detail/check_type.hpp>
#include <sge/cg/parameter/detail/pp_types.hpp>
#include <sge/core/impl/export_function_instantiation.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Type
>
void
sge::cg::parameter::detail::check_type(
	sge::cg::parameter::object const &_parameter
)
{
	FCPPT_ASSERT_ERROR(
		sge::cg::impl::parameter::get_type(
			_parameter
		)
		==
		sge::cg::impl::parameter::type_base_enum<
			Type
		>::value
	);
}

#define SGE_CG_INSTANTIATE_PARAMETER_DETAIL_CHECK_TYPE(\
	seq,\
	_,\
	type\
)\
template \
SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
void \
sge::cg::parameter::detail::check_type<\
	type\
>(\
	sge::cg::parameter::object const &\
);\

BOOST_PP_SEQ_FOR_EACH(
	SGE_CG_INSTANTIATE_PARAMETER_DETAIL_CHECK_TYPE,
	_,
	SGE_CG_PARAMETER_DETAIL_PP_TYPES
)
