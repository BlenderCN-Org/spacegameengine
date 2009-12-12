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


#ifndef SGE_SPRITE_INTRUSIVE_SYSTEM_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_SYSTEM_DECL_HPP_INCLUDED

#include <sge/sprite/intrusive/system_fwd.hpp>
#include <sge/sprite/intrusive/order.hpp>
#include <sge/sprite/system_base_decl.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace sge
{
namespace sprite
{
namespace intrusive
{

template<
	typename Choices
>
class system
:
	public system_base<
		Choices
	>
{
public:
	typedef system_base<
		Choices
	> base;

	typedef sprite::object<
		Choices
	> object;

	explicit system(
		renderer::device_ptr
	);

	~system();

	template<
		typename EqualFunction
	>
	void
	render_all(
		EqualFunction const &
	);

	template<
		typename EqualFunction
	>
	void
	render(
		order,
		EqualFunction const &
	);

	void
	add(
		object &,
		order
	);
private:
	typedef boost::intrusive::list<
		object,
		boost::intrusive::constant_time_size<
			false
		>
	> sprite_list;

	template<
		typename EqualFunction
	>
	void
	render(
		sprite_list const &,
		EqualFunction const &
	);

	typedef boost::ptr_map<
		order,
		sprite_list
	> sprite_level_map;

	sprite_level_map sprite_levels;
};

}
}
}

#endif
