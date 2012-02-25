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


#include <sge/opengl/glx/context.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/text.hpp>


sge::opengl::glx::context::context(
	awl::backends::x11::display &_display,
	XVisualInfo const &_visual_info
)
:
	display_(_display),
	context_(
		::glXCreateContext(
			_display.get(),
			const_cast<
				XVisualInfo *
			>(
				&_visual_info
			),
			fcppt::null_ptr(),
			True
		)
	)
{
	if(
		context_ == fcppt::null_ptr()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("glXCreateContext() failed!")
		);
}

sge::opengl::glx::context::~context()
{
	::glXDestroyContext(
		display_.get(),
		this->get()
	);
}

GLXContext &
sge::opengl::glx::context::get()
{
	return context_;
}
