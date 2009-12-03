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


#ifndef SGE_SPRITE_SYSTEM_DECL_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_DECL_HPP_INCLUDED

#include <sge/sprite/system_fwd.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/system_base.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace sprite
{

template<
	typename Choices,
	typename Elements
>
class system
:
	public system_base
{
public:
	typedef sprite::object<
		Choices,
		Elements
	> object;

	explicit system(
		renderer::device_ptr rend
	);

	template<
		typename Iterator,
		typename SortFunction,
		typename EqualFunction
	>
	void
	render(
		Iterator begin,
		Iterator end,
		SortFunction const &
		EqualFunction const &
	);

	void
	render(
		object_type const &
	);
};

}
}

#endif
