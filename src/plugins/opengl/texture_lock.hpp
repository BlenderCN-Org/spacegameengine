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



#ifndef SGE_OPENGL_TEXTURE_LOCK_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_LOCK_HPP_INCLUDED

#include "lock_method.hpp"
#include <sge/noncopyable.hpp>
#include <cstddef>

namespace sge
{
namespace ogl
{

class texture_lock {
	SGE_NONCOPYABLE(texture_lock)
protected:
	texture_lock();
public:
	// FIXME: make these typedefs consistent!
	typedef std::size_t size_type;
	typedef unsigned char value_type;
	typedef value_type *pointer;
	typedef value_type const *const_pointer;

	virtual ~texture_lock();
		
	virtual void post_lock() = 0;
	
	virtual void pre_unlock() = 0;

	virtual pointer write_pointer() const;

	virtual pointer read_pointer() const;

	virtual pointer real_write_pointer();

	virtual const_pointer real_read_pointer() const;

	virtual lock_method::type method() const = 0;
};

}
}

#endif
