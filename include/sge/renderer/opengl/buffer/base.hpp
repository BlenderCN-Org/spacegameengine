/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_OPENGL_BUFFER_BASE_HPP_INCLUDED
#define SGE_RENDERER_OPENGL_BUFFER_BASE_HPP_INCLUDED

#include <sge/renderer/opengl/buffer/base_fwd.hpp>
#include <sge/renderer/opengl/buffer/id.hpp>
#include <sge/renderer/opengl/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
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
	SGE_RENDERER_OPENGL_DETAIL_SYMBOL
	base();
public:
	SGE_RENDERER_OPENGL_DETAIL_SYMBOL
	virtual
	~base() = 0;

	virtual
	sge::renderer::opengl::buffer::id
	id() const = 0;

	virtual
	bool
	native() const = 0;
};

}
}
}
}

#endif
