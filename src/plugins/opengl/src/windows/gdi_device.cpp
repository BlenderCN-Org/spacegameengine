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


#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>


sge::opengl::windows::gdi_device::gdi_device(
	HWND const _hwnd,
	sge::opengl::windows::gdi_device::get_tag
)
:
	hwnd_(
		_hwnd
	),
	dc_(
		::GetDC(
			_hwnd
		)
	)
{
	if(
		dc_
		==
		nullptr
	)
		throw
			sge::renderer::exception(
				FCPPT_TEXT("GetDC() failed!")
			);
}

sge::opengl::windows::gdi_device::~gdi_device()
{
	::ReleaseDC(
		hwnd_,
		dc_
	);
}

HDC
sge::opengl::windows::gdi_device::hdc() const
{
	return
		dc_;
}
