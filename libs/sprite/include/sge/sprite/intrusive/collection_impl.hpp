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


#ifndef SGE_SPRITE_INTRUSIVE_COLLECTION_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_COLLECTION_IMPL_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/intrusive/collection_decl.hpp>
#include <sge/sprite/intrusive/connection_fwd.hpp>
#include <sge/sprite/intrusive/connection_ref.hpp>
#include <sge/sprite/intrusive/range_impl.hpp>
#include <sge/sprite/intrusive/detail/connection_impl.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>


template<
	typename Choices
>
sge::sprite::intrusive::collection<
	Choices
>::collection()
:
	sprites_(),
	count_(
		0u
	),
	connection_(
		fcppt::make_ref(
			sprites_
		),
		fcppt::make_ref(
			count_
		)
	)
{
}

template<
	typename Choices
>
sge::sprite::intrusive::collection<
	Choices
>::~collection()
{
}

template<
	typename Choices
>
typename
sge::sprite::intrusive::collection<
	Choices
>::connection_ref
sge::sprite::intrusive::collection<
	Choices
>::connection()
{
	typedef
	sge::sprite::intrusive::connection<
		Choices
	> &
	connection_base_ref;

	return
		fcppt::make_ref(
			connection_base_ref(
				connection_
			)
		);
}

template<
	typename Choices
>
typename sge::sprite::intrusive::collection<
	Choices
>::range_type
sge::sprite::intrusive::collection<
	Choices
>::range()
{
	return
		range_type(
			fcppt::make_ref(
				sprites_
			),
			count_
		);
}

template<
	typename Choices
>
typename sge::sprite::intrusive::collection<
	Choices
>::const_range_type
sge::sprite::intrusive::collection<
	Choices
>::range() const
{
	return
		const_range_type(
			fcppt::make_cref(
				sprites_
			),
			count_
		);
}

#endif
