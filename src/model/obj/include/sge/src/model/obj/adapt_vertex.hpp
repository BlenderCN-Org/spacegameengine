/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_MODEL_OBJ_ADAPT_VERTEX_HPP_INCLUDED
#define SGE_SRC_MODEL_OBJ_ADAPT_VERTEX_HPP_INCLUDED

#include <sge/model/obj/optional_scalar.hpp>
#include <sge/model/obj/scalar.hpp>
#include <sge/model/obj/vertex.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_FUSION_ADAPT_STRUCT(
	sge::model::obj::vertex,
	(sge::model::obj::scalar, v1_)
	(sge::model::obj::scalar, v2_)
	(sge::model::obj::scalar, v3_)
	(sge::model::obj::optional_scalar, v4_)
)

FCPPT_PP_POP_WARNING

#endif
