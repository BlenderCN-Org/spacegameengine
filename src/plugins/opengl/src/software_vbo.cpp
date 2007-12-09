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


#if 0
#include <cassert>
#include <map>
#include <utility>

namespace
{

GLuint nextid = 1,
       bound_vb = 0,
       bound_ib = 0,
       bound_pack = 0,
       bound_unpack = 0;

typedef std::map<GLuint, unsigned char*> buffer_map;
buffer_map buffers;

GLuint& get_bound_buffer(GLenum type);
buffer_map::iterator get_buffer_object(GLuint id);
void check_bound(GLenum type);

}

GLuint sge::ogl::gen_buffer()
{
	buffers.insert(std::make_pair(nextid, 0));
	return nextid++;
}

void sge::ogl::delete_buffer(const GLuint id)
{
	const buffer_map::iterator it = get_buffer_object(id);
	assert(it->second);
	delete[] it->second;
	buffers.erase(it);
}

void sge::ogl::bind_buffer(const GLenum type, const GLuint id)
{
	get_bound_buffer(type) = id;
}

void* sge::ogl::map_buffer(const GLenum type, const GLenum flags)
{
	check_bound(type);
}

void sge::ogl::unmap_buffer(const GLenum type)
{
	check_bound(type);
}

void sge::ogl::buffer_data(const GLenum type, const GLsizei size, const void *const data, const GLenum flags)
{
	buffer_sub_data(type, 0, size, data);
}

void sge::ogl::buffer_sub_data(const GLenum type, const GLsizei first, const GLsizei size, const void *const data)
{
	std::copy_n(static_cast<const unsigned char*>(data) + first, size, get_buffer_object(get_bound_buffer(type))->second);
}

void* sge::ogl::buffer_offset(const GLenum type, const GLsizei offset)
{
	return get_buffer_object(get_bound_buffer(type))->second + offset;
}

namespace
{
	
GLuint& get_bound_buffer(const GLenum type)
{
	switch(type) {
	case GL_ARRAY_BUFFER:
		return bound_vb;
	case GL_ELEMENT_ARRAY_BUFFER:
		return bound_ib;
	case GL_PIXEL_PACK_BUFFER:
		return bound_pack;
	case GL_PIXEL_UNPACK_BUFFER:
		return bound_unpack;
	default:
		throw sge::exception("get_bound_buffer(): invalid type!");
	}
}

buffer_map::iterator get_buffer_object(const GLuint id)
{
	const buffer_map::iterator it = buffers.find(id);
	if(it == buffers.end())
		throw sge::exception("get_buffer_object(): invalid id!");
	return it;
}

void check_bound(const GLenum type)
{
	if(get_bound_buffer(type) == 0)
		throw sge::exception("ogl soft buffer: no buffer bound!");
}

}
#endif
