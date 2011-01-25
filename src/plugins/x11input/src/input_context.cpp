/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../input_context.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/text.hpp>
#include <X11/Xlib.h>

sge::x11input::input_context::input_context(
	XIM const _xim,
	std::string const &_class_name,
	awl::backends::x11::window::instance_ptr const _window
)
:
	xic_(
		::XCreateIC(
			_xim,
			XNClientWindow,
			_window->get(),
			XNFocusWindow,
			_window->get(),
			XNInputStyle,
			XIMPreeditNothing | XIMStatusNothing,
			XNResourceName,
			_class_name.c_str(),
			XNResourceClass,
			_class_name.c_str(),
			NULL
		)
	)
{
	if(
		xic_ == NULL
	)
		throw sge::input::exception(
			FCPPT_TEXT("XCreateIC() failed!")
		);
}

sge::x11input::input_context::~input_context()
{
	::XDestroyIC(
		xic_
	);
}

XIC
sge::x11input::input_context::get() const
{
	return xic_;
}
