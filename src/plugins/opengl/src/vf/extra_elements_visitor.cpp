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


#include <sge/image/color/element_count.hpp>
#include <sge/opengl/vf/extra_elements_visitor.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>


GLint
sge::opengl::vf::extra_elements_visitor::operator()(
	renderer::vf::dynamic::vector const &_vector
) const
{
	return
		static_cast<
			GLint
		>(
			_vector.element_count().get()
		);
}

GLint
sge::opengl::vf::extra_elements_visitor::operator()(
	renderer::vf::dynamic::color const &_color
) const
{
	return
		static_cast<
			GLint
		>(
			sge::image::color::element_count(
				_color.color_format()
			)
		);
}
