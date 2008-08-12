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


#ifndef SGE_OPENGL_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_VERTEX_BUFFER_HPP_INCLUDED

#include "buffer_base.hpp"
#include "vertex_format.hpp"
#include "vbo.hpp"
#include <sge/renderer/vertex_buffer.hpp>

namespace sge
{
namespace ogl
{

namespace detail
{
typedef buffer_base<
	renderer::vertex_buffer,
	vertex_buffer_type,
	vb_ib_vbo_impl
> vertex_buffer_base;
}

class vertex_buffer
: public detail::vertex_buffer_base {	
public:
	typedef detail::vertex_buffer_base base;
	using base::view_type;
	using base::const_view_type;
	using base::resource_flag_type;

	vertex_buffer(
		const_view_type const &,
		resource_flag_type flags);

	void set_format();
private:
	view_type const view();
	const_view_type const view() const;

	renderer::vertex_format const &
	get_vertex_format() const;

	renderer::vertex_format format;
	vertex_format ogl_format;
};

}
}

#endif
