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


#ifndef SGE_OPENGL_INDEX_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_INDEX_BUFFER_HPP_INCLUDED

#include "common.hpp"
#include "index_buffer_base.hpp"
#include "vbo.hpp"
#include "basic_buffer.hpp"
#include <sge/renderer/index_buffer.hpp>

namespace sge
{
namespace opengl
{

template<
	typename T
>
class index_buffer
:
	public index_buffer_base
{
public:
	index_buffer(
		size_type sz,
		renderer::resource_flags_field const &
	);

	GLenum
	gl_format() const;

	GLvoid *
	buffer_offset(
		size_type
	) const;

	void
	bind_me() const;
private:
	view_type const
	lock(
		renderer::lock_mode::type,
		size_type offset,
		size_type range
	);

	const_view_type const
	lock(
		size_type offset,
		size_type range
	) const;

	void
	unlock() const;

	size_type
	size() const;

	renderer::resource_flags_field const
	flags() const;

	renderer::index::dynamic::format::type
	format() const;

	typedef basic_buffer<
		index_buffer_type,
		vb_ib_vbo_impl,
		T
	> buffer_type;

	mutable buffer_type buf;
};

}
}

#endif

