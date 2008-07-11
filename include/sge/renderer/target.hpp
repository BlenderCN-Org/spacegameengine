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


#ifndef SGE_RENDERER_TARGET_HPP_INCLUDED
#define SGE_RENDERER_TARGET_HPP_INCLUDED

#include "image_view.hpp"
#include "types.hpp"
#include "../shared_ptr.hpp"
#include "../export.hpp"
#include "../math/dim.hpp"
#include <cstddef>

namespace sge
{
namespace renderer
{

class target {
public:
	typedef std::size_t                    size_type;
	typedef math::basic_dim<size_type, 2>  dim_type;

	virtual void lock() = 0;
	virtual void lock(lock_rect const &dest) = 0;
	virtual void unlock() = 0;

	virtual const dim_type dim() const = 0;
	SGE_SYMBOL size_type size() const;

	virtual const_image_view const view() const = 0;
		
	virtual ~target();
};

typedef shared_ptr<target> target_ptr;

}
}

#endif
