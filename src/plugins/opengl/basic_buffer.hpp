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


#ifndef SGE_OPENGL_BASIC_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_BASIC_BUFFER_HPP_INCLUDED

#include "common.hpp"
#include <sge/renderer/types.hpp>

namespace sge
{
namespace ogl
{

class vbo_base;

template<
	typename Base,
	GLenum (*Type)(),
	vbo_base& (*Impl)()>
class basic_buffer : public Base {
public:
	typedef typename Base::size_type              size_type;
	typedef typename Base::difference_type        difference_type;
	typedef unsigned char                         value_type;
	typedef value_type                           *pointer;
	typedef value_type const                     *const_pointer;
	typedef typename Base::resource_flag_type     resource_flag_type;
	typedef typename Base::lock_flag_type         lock_flag_type;
			
	basic_buffer(
		size_type sz,
		size_type stride,
		resource_flag_type flags,
		const_pointer src);
	~basic_buffer();

	using Base::npos;

	void do_lock(
		lock_flag_type lock_flags,
		size_type first = 0,
		size_type count = npos);
	void do_unlock();
	void data(
		const_pointer,
		size_type stride,
		size_type size);
	void sub_data(
		const_pointer data,
		size_type first,
		size_type count);
	void resize(size_type);

	size_type size() const;
	size_type stride() const;
	resource_flag_type flags() const;

	void resize(
		size_type newsize,
		size_type newstride,
		const_pointer src);

	pointer data();
	const_pointer data() const;
	size_type lock_size() const;

	void unbind() const;
	void bind_me() const;
	
	pointer buffer_offset(
		size_type offset) const;
private:
	void bind(GLuint id) const;
	void check_lock() const;
	void allocate_buffer(const_pointer src);

	size_type          sz,
	                   stride_;
	resource_flag_type flags_;
	pointer            dest;
	GLuint             id;
	size_type          lock_offset,
	                   lock_size_;
};

}
}

#endif
