/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_INTRUSIVE_SYSTEM_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_SYSTEM_HPP_INCLUDED

#include "intrusive_object.hpp"
#include "system_base.hpp"
#include "../renderer/device.hpp"
#include <boost/intrusive/list.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace sprite
{

class intrusive_system : public system_base {
public:
	SGE_SYMBOL explicit intrusive_system(
		renderer::device_ptr);
	
	SGE_SYMBOL void render();
private:
	typedef boost::intrusive::list<
		intrusive_object,
		boost::intrusive::constant_time_size<false>
	> sprite_list;

	void render(
		sprite_list const &);
	void add(
		intrusive_object &,
		bool transparent);
	friend class intrusive_object;

	sprite_list opaque_sprites,
	            transparent_sprites;
};

}
}

#endif
