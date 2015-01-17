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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/viewport.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/target/viewport.hpp>


D3DVIEWPORT9 const
sge::d3d9::convert::viewport(
	sge::renderer::target::viewport const &_viewport
)
{
	sge::renderer::pixel_rect const rect(
		_viewport.get()
	);

	D3DVIEWPORT9 const ret =
	{
		static_cast<
			DWORD
		>(
			rect.left()
		),
		static_cast<
			DWORD
		>(
			rect.top()
		),
		static_cast<
			DWORD
		>(
			rect.size().w()
		),
		static_cast<
			DWORD
		>(
			rect.size().h()
		),
		0.f,
		1.f
	};

	return ret;
}
