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


#include "../../../exception.hpp"
#include "../vbo.hpp"
#include "../error.hpp"
#include "../extension.hpp"
#include "../version.hpp"

void sge::ogl::check_vbo_extension()
{

#ifdef SGE_OGL_VERTEX_BUFFER_OBJECT_ARB
		if(!glGenBuffersARB)
			throw exception(extension_not_supported_string("GL_ARB_vertex_buffer_object"));
#else
		if(!glGenBuffers)
			throw exception(version_not_supported_string("glGenBuffers", "1.5"));
#endif

}

GLuint sge::ogl::gen_buffer()
{
	GLuint id;
#ifdef SGE_OGL_VERTEX_BUFFER_OBJECT_ARB
	glGenBuffersARB(1, &id);
#else
	glGenBuffers(1, &id);
#endif
	if(is_error())
		throw exception("glGenBuffers() failed!");

	return id;
}

void sge::ogl::delete_buffer(const GLuint id)
{
#ifdef SGE_OGL_VERTEX_BUFFER_OBJECT_ARB
	glDeleteBuffersARB(1, &id);
#else
	glDeleteBuffers(1, &id);
#endif
}

void sge::ogl::bind_buffer(const GLenum type, const GLuint id)
{
#ifdef SGE_OGL_VERTEX_BUFFER_OBJECT_ARB
	glBindBufferARB(type, id);
#else
	glBindBuffer(type, id);
#endif
	if(is_error())
		throw exception("glBindBuffer() failed!");
}

void* sge::ogl::map_buffer(const GLenum type, const GLenum flags)
{
	void *const ret = 
#ifdef SGE_OGL_VERTEX_BUFFER_OBJECT_ARB
	glMapBufferARB(type, flags);
#else
	glMapBuffer(type, flags);
#endif
	if(ret == 0)
		throw exception("glMapBuffer() returned 0!");
	if(is_error())
		throw exception("glMapBuffer() failed!");
	return ret;
}

void sge::ogl::unmap_buffer(const GLenum type)
{
#ifdef SGE_OGL_VERTEX_BUFFER_OBJECT_ARB
	glUnmapBufferARB(type);
#else
	glUnmapBuffer(type);
#endif
	if(is_error())
		throw exception("glUnmapBuffer() failed!");
}

void sge::ogl::buffer_data(const GLenum type, const GLsizei size, const void *const data, const GLenum flags)
{
#ifdef SGE_OGL_VERTEX_BUFFER_OBJECT_ARB
	glBufferDataARB(type, size, data, flags);
#else
	glBufferData(type, size, data, flags);
#endif
	if(is_error())
		throw exception("glBufferData() failed!");
}

void sge::ogl::buffer_sub_data(const GLenum type, const GLsizei first, const GLsizei size, const void *const data)
{
#ifdef SGE_OGL_VERTEX_BUFFER_OBJECT_ARB
	glBufferSubDataARB(type, first, size, data);
#else
	glBufferSubData(type, first, size, data);
#endif
	if(is_error())
		throw exception("glBufferSubData() failed!");

}
