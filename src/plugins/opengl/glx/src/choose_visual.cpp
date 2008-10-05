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


#include "../choose_visual.hpp"
#include <GL/glx.h>
#include <sge/raw_vector_impl.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::glx::visual_attribute_array const
sge::ogl::glx::choose_visual(
	renderer::bit_depth::type const bit_depth,
	renderer::depth_buffer::type const depth_buffer,
	renderer::stencil_buffer::type const stencil_buffer)
{
	visual_attribute_array ret;
	ret.push_back(GLX_RGBA);
	ret.push_back(GLX_DOUBLEBUFFER);

	switch(bit_depth) {
	case renderer::bit_depth::depth16:
		//  FIXME
		//t.push_back(
		break;
	case renderer::bit_depth::depth32:
		ret.push_back(GLX_RED_SIZE);
		ret.push_back(8);
		ret.push_back(GLX_BLUE_SIZE);
		ret.push_back(8);
		ret.push_back(GLX_GREEN_SIZE);
		ret.push_back(8);
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid bit_depth!"));
	}

	if(depth_buffer != renderer::depth_buffer::off)
	{
		ret.push_back(GLX_DEPTH_SIZE);
		ret.push_back(static_cast<int>(depth_buffer)); // TODO
	}

	if(stencil_buffer != renderer::stencil_buffer::off)
	{
		ret.push_back(GLX_STENCIL_SIZE);
		ret.push_back(static_cast<int>(stencil_buffer));
	}
	ret.push_back(None);
	return ret;
}	
