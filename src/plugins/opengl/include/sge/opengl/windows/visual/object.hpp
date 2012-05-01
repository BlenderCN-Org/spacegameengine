/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_WINDOWS_VISUAL_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_WINDOWS_VISUAL_OBJECT_HPP_INCLUDED

#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/visual/object.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace windows
{
namespace visual
{

class object
:
	public awl::backends::windows::visual::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::renderer::bit_depth::type,
		sge::renderer::depth_stencil_buffer::type
	);

	~object();
private:
	void
	apply(
		HWND
	) const;

	sge::renderer::bit_depth::type const bit_depth_;

	sge::renderer::depth_stencil_buffer::type const depth_stencil_;
};

}
}
}
}

#endif