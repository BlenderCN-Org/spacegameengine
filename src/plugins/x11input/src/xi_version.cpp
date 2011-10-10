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


#include <sge/x11input/xi_version.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

bool
sge::x11input::xi_version(
	awl::backends::x11::display &_display,
	int const _major,
	int const _minor
)
{
	// BadRequest will be generated if the
	// server doesn't support XI2 at all.
	// Otherwise the version the server actually supports is returned.

	int
		major_ret(
			_major
		),
		minor_ret(
			_minor
		);
	return
		::XIQueryVersion(
			_display.get(),
			&major_ret,
			&minor_ret
		)
		!= BadRequest
		&&
		(
			major_ret > _major
			||
			(
				_major == major_ret
				&& minor_ret >= _minor
			)
		);
}
