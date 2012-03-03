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


#ifndef ALDA_BINDINGS_FUNDAMENTAL_HPP_INCLUDED
#define ALDA_BINDINGS_FUNDAMENTAL_HPP_INCLUDED

#include <alda//endianness.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/fundamental.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/concepts/static_size.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <fcppt/endianness/from_host.hpp>
#include <fcppt/endianness/to_host.hpp>


namespace alda
{
namespace bindings
{

template<
	typename T
>
struct fundamental
:
majutsu::fundamental<
	T
>
{};

template<
	typename Type
>
void
place(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	alda::bindings::fundamental<
		Type
	> const *,
	Type const &_type,
	majutsu::raw_pointer const _mem
)
{
	place(
		_tag,
		static_cast<
			majutsu::fundamental<
				Type
			> const *
		>(
			0
		),
		fcppt::endianness::from_host(
			_type,
			alda::endianness()
		),
		_mem
	);
}

template<
	typename Type
>
Type
make(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	alda::bindings::fundamental<
		Type
	> const *,
	majutsu::const_raw_pointer const _beg
)
{
	return
		fcppt::endianness::to_host(
			make(
				_tag,
				static_cast<
					majutsu::fundamental<
						Type
					> const *
				>(
					0
				),
				_beg
			),
			alda::endianness()
		);
}

}
}

namespace majutsu
{
namespace concepts
{

template<
	typename Type
>
struct static_size<
	alda::bindings::fundamental<
		Type
	>
>
:
static_size<
	majutsu::fundamental<
		Type
	>
>
{};

}
}

#endif
