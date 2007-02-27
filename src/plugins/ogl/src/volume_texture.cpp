/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../volume_texture.hpp"
#include "../error.hpp"

sge::ogl::volume_texture::volume_texture(const const_pointer src, const size_type _width, const size_type _height, const size_type _depth, const filter_args& filter, const resource_flag_t flags)
 : basic_texture<sge::volume_texture,GL_TEXTURE_3D>(filter,flags),
   _width(_width),
   _height(_height),
   _depth(_depth)
{
	set_data(src);
}

sge::ogl::volume_texture::size_type sge::ogl::volume_texture::size() const
{
	return width()*height()*depth();
}

sge::ogl::volume_texture::size_type sge::ogl::volume_texture::width() const
{
	return _width; 
}

sge::ogl::volume_texture::size_type sge::ogl::volume_texture::height() const
{
	return _height;
}

sge::ogl::volume_texture::size_type sge::ogl::volume_texture::depth() const
{
	return _depth;
}

void sge::ogl::volume_texture::set_data(const const_pointer src, const lock_box* const b)
{
	bind_me();
	set_my_filter();
	const GLenum format = GL_RGBA, type = GL_UNSIGNED_BYTE;
	if(!b)
		glTexImage3D(GL_TEXTURE_3D,0,4,width(),height(),depth(),0,format,type,src);
	else
		glTexSubImage3D(GL_TEXTURE_3D,0,b->left,b->top,b->front,b->width(),b->height(),b->depth(),format,type,src);
	if(is_error())
		throw std::runtime_error("glTex(Sub)Image3D failed!");
}

