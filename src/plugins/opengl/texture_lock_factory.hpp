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


#ifndef SGE_OGL_TEXTURE_LOCK_FACTORY_HPP_INCLUDED
#define SGE_OGL_TEXTURE_LOCK_FACTORY_HPP_INCLUDED

#include "texture_lock.hpp"
#include "lock_method.hpp"
#include <sge/renderer/resource_flags.hpp>
#include <memory>

namespace sge
{
namespace ogl
{

typedef std::auto_ptr<texture_lock> texture_lock_auto_ptr;

texture_lock_auto_ptr create_texture_lock(
	lock_method::type,
	texture_lock::size_type lock_size,
	texture_lock::size_type offset,
	texture_lock::size_type whole_size,
	texture_lock::size_type stride,
	texture_lock::size_type pitch,
	renderer::resource_flag_t flags);

}
}

#endif
