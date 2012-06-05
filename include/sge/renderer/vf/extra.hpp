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


#ifndef SGE_RENDERER_VF_EXTRA_HPP_INCLUDED
#define SGE_RENDERER_VF_EXTRA_HPP_INCLUDED

#include <sge/renderer/vf/color_base.hpp>
#include <sge/renderer/vf/element_count_type.hpp>
#include <sge/renderer/vf/extra_base.hpp>
#include <sge/renderer/vf/extra_fwd.hpp>
#include <sge/renderer/vf/vector_base.hpp>
#include <sge/renderer/vf/vector_fwd.hpp>
#include <mizuiro/color/homogenous_static_fwd.hpp>
#include <fcppt/static_assert_statement.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Format,
	sge::renderer::vf::element_count_type NumSubElements,
	typename Index
>
struct extra<
	sge::renderer::vf::vector<
		Format,
		NumSubElements
	>,
	Index
>
:
sge::renderer::vf::extra_base<
	sge::renderer::vf::vector_base<
		Format,
		NumSubElements
	>,
	Index
>
{
	FCPPT_STATIC_ASSERT_STATEMENT(
		boost::is_fundamental<
			Format
		>::value
	);

	FCPPT_STATIC_ASSERT_STATEMENT(
		NumSubElements >= 1
		&& NumSubElements <= 4
	);
};

template<
	typename ColorChannel,
	typename ColorLayout,
	typename Index
>
struct extra<
	mizuiro::color::homogenous_static<
		ColorChannel,
		ColorLayout
	>,
	Index
>
:
sge::renderer::vf::extra_base<
	sge::renderer::vf::color_base<
		mizuiro::color::homogenous_static<
			ColorChannel,
			ColorLayout
		>
	>,
	Index
>
{
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
