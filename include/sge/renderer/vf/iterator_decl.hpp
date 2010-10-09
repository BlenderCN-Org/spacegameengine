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


#ifndef SGE_RENDERER_VF_ITERATOR_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_ITERATOR_DECL_HPP_INCLUDED

#include <sge/renderer/vf/iterator_fwd.hpp>
#include <sge/renderer/vf/detail/iterator_base.hpp>
#include <boost/iterator/iterator_facade.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename VertexFormat
>
class iterator
:
	public detail::iterator_base<
		VertexFormat
	>::type
{
	typedef typename detail::iterator_base<VertexFormat>::type base;
public:
	typedef typename base::value_type value_type;
	typedef typename base::reference reference;
	typedef typename base::pointer pointer;
	typedef typename base::difference_type difference_type;
	typedef typename base::iterator_category iterator_category;
private:
	typedef value_type vertex_type;

	typedef typename vertex_type::pointer internal_pointer;

	static difference_type
	stride();

	explicit iterator(
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
		typename
	> friend class view;
};

}
}
}

#endif
