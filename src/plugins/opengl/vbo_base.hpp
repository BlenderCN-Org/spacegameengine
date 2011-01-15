/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_VBO_BASE_HPP_INCLUDED
#define SGE_OPENGL_VBO_BASE_HPP_INCLUDED

#include "vbo_base_fwd.hpp"
#include "common.hpp"
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class vbo_base
{
	FCPPT_NONCOPYABLE(vbo_base)
protected:
	vbo_base();
public:
	virtual GLuint
	gen_buffer() = 0;

	virtual void
	delete_buffer(
		GLuint
	) = 0;

	virtual void
	bind_buffer(
		GLenum type,
		GLuint
	) = 0;

	virtual GLvoid *
	map_buffer(
		GLenum type,
		GLenum flags
	) = 0;

	virtual GLvoid *
	map_buffer_range(
		GLenum type,
		GLenum flags,
		GLsizei first,
		GLsizei size
	) = 0;

	virtual bool
	map_buffer_range_supported() const = 0;

	virtual void
	unmap_buffer(
		GLenum type
	) = 0;

	virtual void
	buffer_data(
		GLenum type,
		GLsizei size,
		GLvoid const *data,
		GLenum flags
	) = 0;

	virtual void
	buffer_sub_data(
		GLenum type,
		GLsizei first,
		GLsizei size,
		GLvoid const *data
	) = 0;

	virtual GLvoid *
	buffer_offset(
		GLenum type,
		GLsizei offset
	) const = 0;

	virtual bool
	hardware_supported() const = 0;

	virtual ~vbo_base();
};

}
}

#endif
