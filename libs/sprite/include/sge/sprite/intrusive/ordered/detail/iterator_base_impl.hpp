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


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_ITERATOR_BASE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_ITERATOR_BASE_IMPL_HPP_INCLUDED

#include <sge/sprite/intrusive/ordered/iterator_fwd.hpp>
#include <sge/sprite/intrusive/ordered/detail/range_iterator.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <iterator>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace ordered
{
namespace detail
{

template<
	typename Choices,
	typename Order,
	bool IsConst
>
struct iterator_base_impl
{
	typedef
	std::iterator_traits<
		sge::sprite::intrusive::ordered::detail::range_iterator<
			Choices,
			IsConst
		>
	>
	range_iterator_traits;

	typedef
	boost::iterator_facade<
		sge::sprite::intrusive::ordered::iterator<
			Choices,
			Order,
			IsConst
		>,
		typename
		range_iterator_traits::value_type,
		std::forward_iterator_tag,
		typename
		range_iterator_traits::reference,
		typename
		range_iterator_traits::difference_type
	>
	type;
};

}
}
}
}
}

#endif
