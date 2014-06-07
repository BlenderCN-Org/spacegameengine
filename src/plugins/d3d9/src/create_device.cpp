/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/d3d9/create_device.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/parameters/tnl_caps.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/device/index.hpp>
#include <fcppt/text.hpp>


sge::d3d9::d3d_device_unique_ptr
sge::d3d9::create_device(
	IDirect3D9 &_system,
	sge::renderer::device::index const _index,
	D3DPRESENT_PARAMETERS &_parameters
)
{
	IDirect3DDevice9 *ret;

	if(
		_system.CreateDevice(
			_index.get(),
			D3DDEVTYPE_HAL,
			_parameters.hDeviceWindow,
			sge::d3d9::parameters::tnl_caps(
				_system,
				_index
			),
			&_parameters,
			&ret
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Failed to initialize the d3d9 renderer!")
		);

	return
		sge::d3d9::d3d_device_unique_ptr(
			ret
		);
}
