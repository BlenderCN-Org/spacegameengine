/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_BUFFER_BASE_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_BASE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base_fwd.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id_fwd.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual
	~base() = 0;

	virtual
	sge::opengl::buffer::id const
	gen_buffer() = 0;

	virtual
	void
	delete_buffer(
		sge::opengl::buffer::id
	) = 0;

	virtual
	void
	bind_buffer(
		sge::opengl::buffer::type,
		sge::opengl::buffer::optional_id const &
	) = 0;

	virtual
	GLvoid *
	map_buffer(
		sge::opengl::buffer::type,
		GLenum flags
	) = 0;

	virtual
	GLvoid *
	map_buffer_range(
		sge::opengl::buffer::type,
		GLenum flags,
		GLsizei first,
		GLsizei size
	) = 0;

	virtual
	bool
	map_buffer_range_supported() const = 0;

	virtual
	void
	unmap_buffer(
		sge::opengl::buffer::type
	) = 0;

	virtual
	void
	buffer_data(
		sge::opengl::buffer::type,
		GLsizei size,
		GLvoid const *data,
		GLenum flags
	) = 0;

	virtual
	void
	buffer_sub_data(
		sge::opengl::buffer::type,
		GLsizei first,
		GLsizei size,
		GLvoid const *data
	) = 0;

	virtual
	GLvoid *
	buffer_offset(
		sge::opengl::buffer::type,
		GLsizei offset
	) const = 0;

	virtual
	bool
	hardware_supported() const = 0;
};

}
}
}

#endif
