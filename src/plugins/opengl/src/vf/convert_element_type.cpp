/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/vf/convert_element_type.hpp>
#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::vf::convert_element_type(
	sge::renderer::vf::dynamic::element_type const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::vf::dynamic::element_type::float_:
		return GL_FLOAT;
	case sge::renderer::vf::dynamic::element_type::double_:
		return GL_DOUBLE;
	case sge::renderer::vf::dynamic::element_type::byte:
		return GL_BYTE;
	case sge::renderer::vf::dynamic::element_type::ubyte:
		return GL_UNSIGNED_BYTE;
	case sge::renderer::vf::dynamic::element_type::short_:
		return GL_SHORT;
	case sge::renderer::vf::dynamic::element_type::ushort:
		return GL_UNSIGNED_SHORT;
	case sge::renderer::vf::dynamic::element_type::int_:
		return GL_INT;
	case sge::renderer::vf::dynamic::element_type::uint:
		return GL_UNSIGNED_INT;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
