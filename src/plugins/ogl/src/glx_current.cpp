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


#include "../../../types.hpp"
#ifdef SGE_LINUX_PLATFORM
#include "../../../exception.hpp"
#include "../../../x_window.hpp"
#include "../glx_current.hpp"
#include "../glx_context.hpp"
#include <GL/glx.h>

sge::ogl::glx_current::glx_current(const x_display_ptr dsp, const x_window& wnd, const glx_context_ptr context)
: dsp(dsp),
  context(context)
{
	if(glXMakeCurrent(dsp->get(), wnd.get_window(), context->context()) == false)
		throw exception("glXMakeCurrent() failed");
}

sge::ogl::glx_current::~glx_current()
{
	glXMakeCurrent(dsp->get(), None, NULL);
}

#endif
