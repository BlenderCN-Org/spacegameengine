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


#ifndef SGE_SPRITE_DEFAULTS_POS_HPP_INCLUDED
#define SGE_SPRITE_DEFAULTS_POS_HPP_INCLUDED

#include <sge/sprite/vector.hpp>
#include <sge/sprite/defaults/fwd.hpp>
#include <sge/sprite/roles/pos.hpp>


namespace sge
{
namespace sprite
{

template<
	typename Choices
>
struct defaults<
	Choices,
	roles::pos
>
{
	typedef typename sge::sprite::vector<
		typename Choices::type_choices::unit_type
	>::type type;

	static type const
	get()
	{
		return type::null();
	}
};

}
}

#endif
