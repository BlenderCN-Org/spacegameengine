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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/viewport.hpp>
#include <sge/d3d9/devicefuncs/set_viewport.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <fcppt/text.hpp>


void
sge::d3d9::devicefuncs::set_viewport(
	IDirect3DDevice9 &_device,
	sge::renderer::target::viewport const &_viewport
)
{
	D3DVIEWPORT9 const d3d_viewport(
		sge::d3d9::convert::viewport(
			_viewport
		)
	);

	if(
		_device.SetViewport(
			&d3d_viewport
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("SetViewport() failed!")
		);
}
