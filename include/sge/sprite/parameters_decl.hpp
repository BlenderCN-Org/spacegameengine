/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_SPRITE_PARAMETERS_DECL_HPP_INCLUDED

#include <sge/sprite/parameters_fwd.hpp>
#include <sge/sprite/detail/make_class.hpp>
#include <majutsu/role_return_type.hpp>

namespace sge
{
namespace sprite
{

template<
	typename Choices,
	typename Elements
>
class parameters
{
	typedef typename detail::make_class<
		Choices,
		Elements
	>::type elements_type;
public:
	parameters();

	template<
		typename Role
	>
	parameters const
	set(
		typename majutsu::role_return_type<
			typename elements_type::memory_type::types,
			Role
		>::type const &
	) const;

	elements_type const &
	elements() const;
private:
	elements_type elements_;
};

}
}

#endif
