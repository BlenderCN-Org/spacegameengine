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


#ifndef SGE_RENDERER_INDEX_ITERATOR_DECL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ITERATOR_DECL_HPP_INCLUDED

#include <sge/renderer/index/iterator_fwd.hpp>
#include <sge/renderer/index/detail/iterator_base.hpp>
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
namespace index
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Format
>
class iterator final
:
	public sge::renderer::index::detail::iterator_base<
		Format
	>
{
public:
	typedef
	sge::renderer::index::detail::iterator_base<
		Format
	>
	base;

	typedef
	typename
	base::value_type
	value_type;

	typedef
	typename
	base::reference
	reference;

	typedef
	typename
	Format::pointer
	pointer;

	typedef
	typename
	base::difference_type
	difference_type;

	typedef
	typename
	base::iterator_category
	iterator_category;

	friend class boost::iterator_core_access;

	explicit
	iterator(
		pointer
	);

	pointer
	data() const;
private:
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

	reference
	dereference() const;

	pointer data_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
