/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_WGL_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_WGL_CONTEXT_HPP_INCLUDED

#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/wgl/context_fwd.hpp>
#include <sge/opengl/wgl/context_holder.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace wgl
{

class context
:
	public sge::opengl::backend::context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	explicit
	context(
		awl::backends::windows::window::object &
	);

	~context()
	override;
private:
	sge::opengl::backend::current_unique_ptr
	activate()
	override;

	void
	deactivate(
		sge::opengl::backend::current_unique_ptr &&
	)
	override;

	sge::opengl::windows::gdi_device const gdi_device_;

	sge::opengl::wgl::context_holder const context_;
};

}
}
}

#endif
