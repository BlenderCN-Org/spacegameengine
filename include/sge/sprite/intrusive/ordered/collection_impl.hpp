/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_COLLECTION_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_COLLECTION_IMPL_HPP_INCLUDED

#include <sge/sprite/intrusive/collection_impl.hpp>
#include <sge/sprite/intrusive/connection_ref.hpp>
#include <sge/sprite/intrusive/ordered/collection_decl.hpp>
#include <sge/sprite/intrusive/ordered/range_impl.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/container/get_or_insert.hpp>


template<
	typename Choices,
	typename Order
>
sge::sprite::intrusive::ordered::collection<
	Choices,
	Order
>::collection()
:
	collections_()
{
}

template<
	typename Choices,
	typename Order
>
sge::sprite::intrusive::ordered::collection<
	Choices,
	Order
>::~collection()
{
}

template<
	typename Choices,
	typename Order
>
typename sge::sprite::intrusive::ordered::collection<
	Choices,
	Order
>::collection_base &
sge::sprite::intrusive::ordered::collection<
	Choices,
	Order
>::get(
	order const &_order
)
{
	return
		*fcppt::container::get_or_insert(
			collections_,
			_order,
			[](
				Order
			)
			{
				return
					fcppt::make_unique_ptr<
						sge::sprite::intrusive::collection<
							Choices
						>
					>();
			}
		);
}

template<
	typename Choices,
	typename Order
>
typename
sge::sprite::intrusive::ordered::collection<
	Choices,
	Order
>::connection_ref
sge::sprite::intrusive::ordered::collection<
	Choices,
	Order
>::connection(
	order const &_order
)
{
	return
		this->get(
			_order
		).connection();
}
template<
	typename Choices,
	typename Order
>
typename sge::sprite::intrusive::ordered::collection<
	Choices,
	Order
>::range_type
sge::sprite::intrusive::ordered::collection<
	Choices,
	Order
>::range()
{
	return
		range_type(
			fcppt::make_ref(
				collections_
			)
		);
}

template<
	typename Choices,
	typename Order
>
typename sge::sprite::intrusive::ordered::collection<
	Choices,
	Order
>::const_range_type
sge::sprite::intrusive::ordered::collection<
	Choices,
	Order
>::range() const
{
	return
		const_range_type(
			fcppt::make_ref(
				collections_
			)
		);
}

template<
	typename Choices,
	typename Order
>
template<
	typename Function
>
void
sge::sprite::intrusive::ordered::collection<
	Choices,
	Order
>::for_each(
	Function const &_function
)
{
	for(
		auto const &element
		:
		collections_
	)
		_function(
			element.second->range()
		);
}

#endif
