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


#ifndef SGE_RENDERER_VF_ITERATOR_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_ITERATOR_DECL_HPP_INCLUDED

#include <sge/renderer/vf/iterator_fwd.hpp>
#include <sge/renderer/vf/detail/iterator_base.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/iterator_facade.hpp>
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
	typename Part,
	typename Constness
>
class iterator
:
	public detail::iterator_base<
		Part,
		Constness
	>::type
{
	typedef typename sge::renderer::vf::detail::iterator_base<
		Part,
		Constness
	>::type base;
public:
	typedef typename base::value_type value_type;

	typedef typename base::reference reference;

	typedef typename base::pointer pointer;

	typedef typename base::difference_type difference_type;

	typedef typename base::iterator_category iterator_category;
private:
	typedef value_type vertex_type;

	typedef typename vertex_type::pointer internal_pointer;

	static
	difference_type
	stride();

	explicit
	iterator(
		internal_pointer
	);

	friend class boost::iterator_core_access;

	void
	advance(
		difference_type
	);

	void
	increment();

	void
	decrement();

	bool
	equal(
		iterator const &
	) const;

	difference_type
	distance_to(
		iterator const &
	) const;

	vertex_type
	dereference() const;

	internal_pointer data_;

	template<
		typename,
		typename
	> friend class view;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
