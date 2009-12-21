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


#ifndef SGE_OPENGL_READONLY_TEXTURE_LOCK_HPP_INCLUDED
#define SGE_OPENGL_READONLY_TEXTURE_LOCK_HPP_INCLUDED

#include "texture_lock.hpp"
#include "pixel_pack_buffer.hpp"
#include <sge/renderer/resource_flags_field.hpp>
#include <fcppt/container/raw_vector_decl.hpp>

namespace sge
{
namespace opengl
{

class readonly_texture_lock : public texture_lock {
public:
	readonly_texture_lock(
		size_type lock_size,
		size_type offset,
		size_type whole_size,
		size_type stride,
		size_type pitch,
		size_type block_size,
		renderer::resource_flags_field const &
	);

	void post_lock();
	void do_lock();
	void copy_read_part(pointer dest) const;
	void pre_unlock();
	pointer read_pointer() const;
	const_pointer real_read_pointer() const;
private:
	lock_method::type method() const;

	pixel_pack_buffer buffer;
	size_type
		lock_size,
		offset,
		pitch,
		block_size;

	typedef fcppt::container::raw_vector<
		value_type
	> cutout_buffer_type;

	cutout_buffer_type cutout_buffer;
};

}
}

#endif
