/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
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


#include "../readwrite_texture_lock.hpp"
#include <sge/raw_vector_impl.hpp>

sge::ogl::readwrite_texture_lock::readwrite_texture_lock(
	size_type const lock_size,
	size_type const offset,
	size_type const whole_size,
	size_type const stride,
	size_type const pitch,
	size_type const block_size,
	renderer::resource_flag_t const flags)
:
	read_lock(
		lock_size,
		offset,
		whole_size,
		stride,
		pitch,
		block_size,
		flags),
	write_lock(
	  	lock_size,
		stride,
		flags)
{}

void sge::ogl::readwrite_texture_lock::post_lock()
{
	// skip copying the read pointer to its internal
	// buffer because we can copy it directly
	// to the write buffer
	read_lock.do_lock();
	write_lock.post_lock();

	read_lock.copy_read_part(
		real_write_pointer());
	
	read_lock.pre_unlock();
}

void sge::ogl::readwrite_texture_lock::pre_unlock()
{
	write_lock.pre_unlock();
}

sge::ogl::readwrite_texture_lock::pointer
sge::ogl::readwrite_texture_lock::read_pointer() const
{
	return read_lock.read_pointer();
}

sge::ogl::readwrite_texture_lock::pointer
sge::ogl::readwrite_texture_lock::write_pointer() const
{
	return write_lock.write_pointer();
}

sge::ogl::readwrite_texture_lock::const_pointer
sge::ogl::readwrite_texture_lock::real_read_pointer() const
{
	return write_lock.write_pointer();
}

sge::ogl::readwrite_texture_lock::pointer
sge::ogl::readwrite_texture_lock::real_write_pointer()
{
	return write_lock.real_write_pointer();
}

sge::ogl::lock_method::type
sge::ogl::readwrite_texture_lock::method() const
{
	return lock_method::readwrite;
}
