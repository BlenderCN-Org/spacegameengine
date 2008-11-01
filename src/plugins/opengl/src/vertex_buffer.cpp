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


#include "../vertex_buffer.hpp"
#include "../vbo.hpp"
#include "../instantiate_buffer_base.hpp"
#include "../convert_vertex_colors.hpp"
#include <boost/foreach.hpp>
#include <cassert>

SGE_OPENGL_INSTANTIATE_BUFFER_BASE(
	sge::renderer::vertex_buffer,
	sge::ogl::vertex_buffer_type,
	sge::ogl::vb_ib_vbo_impl)

sge::ogl::vertex_buffer::vertex_buffer(
	renderer::vf::dynamic_format const &format_,
	size_type const sz,
	resource_flag_type const flags)
:
	detail::vertex_buffer_base(
		sz,
		format_.stride(),
		flags,
		0),
	format_(format_)
{}

void sge::ogl::vertex_buffer::set_format() const
{
	bind_me();
	format_.use_me();
}

sge::ogl::vertex_buffer::view_type const
sge::ogl::vertex_buffer::view()
{
	return view_type(
		detail::vertex_buffer_base::data(),
		detail::vertex_buffer_base::lock_size(),
		format());
}

sge::ogl::vertex_buffer::const_view_type const
sge::ogl::vertex_buffer::view() const
{
	return const_view_type(
		detail::vertex_buffer_base::data(),
		detail::vertex_buffer_base::lock_size(),
		format());
}

sge::renderer::vf::dynamic_format const &
sge::ogl::vertex_buffer::format() const
{
	return format_.get();
}

void sge::ogl::vertex_buffer::pre_unlock() const
{
	renderer::vf::dynamic_ordered_element_list const &elems(
		format().elements());
	
	renderer::size_type const stride(
		format().stride());

	assert(lock_size() % stride == 0);

	BOOST_FOREACH(renderer::vf::dynamic_ordered_element_list::const_reference elem, elems)
		if(elem.element().role() == renderer::vf::role::color)
			convert_vertex_colors(
				elem,
				stride,
				lock_size() / stride,
				const_cast<unsigned char *>(data())); // FIXME
}
