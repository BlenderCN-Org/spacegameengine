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


#include "../convert_format.hpp"
#include "../../color_convert.hpp"
#include <sge/renderer/vf/dynamic_vector.hpp>
#include <sge/renderer/vf/dynamic_color.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

GLenum sge::opengl::vf::convert_format::operator()(
	renderer::vf::dynamic_vector const &v) const
{
	switch(v.element_type()) {
	case renderer::vf::element_type::float_:
		return GL_FLOAT;
	case renderer::vf::element_type::double_:
		return GL_DOUBLE;
	case renderer::vf::element_type::byte:
		return GL_UNSIGNED_BYTE;
	default:
		throw exception(
			FCPPT_TEXT("Invalid format in ogl::vf::convert_format!"));
	}
}

GLenum sge::opengl::vf::convert_format::operator()(
	renderer::vf::dynamic_color const &c) const
{
	return to_format_type(
		c.color_format());
}
