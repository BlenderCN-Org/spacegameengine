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


#ifndef SGE_RENDERER_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_HPP_INCLUDED

#include <sge/export.hpp>
#include <sge/renderer/texture_base.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture_pos_type.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL texture : public texture_base {
public:
	typedef renderer::dim_type dim_type;
	typedef lock_rect          rect_type;
	typedef texture_pos_type   pos_type;

	virtual dim_type const dim() const = 0;
	
	SGE_SYMBOL image_view const lock(lock_flag_t);
	SGE_SYMBOL const_image_view const lock() const;

	virtual image_view const lock(lock_rect const &, lock_flag_t) = 0;
	virtual const_image_view const lock(lock_rect const &) const = 0;

	virtual void unlock() const = 0;
	SGE_SYMBOL rect_type const rect() const;

	SGE_SYMBOL size_type content() const;
};

}
}

#endif
