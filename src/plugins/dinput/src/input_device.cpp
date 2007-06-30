/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <stdexcept>
#include "../../../util.hpp"
#include "../input_device.hpp"

const DWORD sge::dinput::input_device::coop_level(DISCL_FOREGROUND | DISCL_EXCLUSIVE);
const DIPROPDWORD sge::dinput::input_device::buffer_settings = {
	sizeof(DIPROPDWORD),
	sizeof(DIPROPHEADER),
	0,
	DIPH_DEVICE,
	buffer_size
};

sge::dinput::input_device::input_device(const dinput_ptr di, const string& _name, const GUID guid, const HWND wnd)
: _name(_name)
{
	direct_input_device* d;
	if(di->CreateDevice(guid,&d,0) != DI_OK)
		throw std::runtime_error("dinput: cannot create input device");
	device.reset(d);
	set_cooperative_level(wnd,coop_level);
	set_property(DIPROP_BUFFERSIZE,&buffer_settings.diph);
}

void sge::dinput::input_device::set_cooperative_level(const HWND hwnd, const DWORD flags)
{
	if(device->SetCooperativeLevel(hwnd,flags) != DI_OK)
		throw std::runtime_error("SetCooperativeLevel() failed");
}

void sge::dinput::input_device::set_data_format(const LPCDIDATAFORMAT df)
{
	if(device->SetDataFormat(df) != DI_OK)
		throw std::runtime_error("SetDataFormat() failed");
}

void sge::dinput::input_device::set_property(REFGUID guid, LPCDIPROPHEADER diph)
{
	if(device->SetProperty(guid,diph) != DI_OK)
		throw std::runtime_error("SetProperty() failed");
}

void sge::dinput::input_device::acquire()
{
	HRESULT res;
	while((res = device->Acquire()) == DIERR_OTHERAPPHASPRIO)
		sge::sleep(100);
	switch(res) {
	case S_FALSE:
	case DI_OK:
		break;
	case DIERR_OTHERAPPHASPRIO:
		break;
	default:
		throw std::runtime_error("Acquire() failed");
	}
}

void sge::dinput::input_device::poll()
{
	if(device->Poll() != DI_OK)
		throw std::runtime_error("Poll() failed");
}

bool sge::dinput::input_device::_get_input(input_buffer data, DWORD& elements)
{
	elements = sizeof(input_buffer) / sizeof(DIDEVICEOBJECTDATA);
	const HRESULT res = device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), data, &elements, 0);
	switch(res) {
	case DI_OK:
	case DI_BUFFEROVERFLOW:
		return true;
	case DIERR_INPUTLOST:
		acquire();
		return _get_input(data,elements);
	case DIERR_NOTACQUIRED:
		acquire();
		return false;
	default:
		throw std::runtime_error("GetDeviceData() failed");
	}
}

void sge::dinput::input_device::enum_objects(LPDIENUMDEVICEOBJECTSCALLBACK fun)
{
	if(device->EnumObjects(fun,this,DIDFT_ALL) != DI_OK)
		throw std::runtime_error("enumerating objects failed");
}

const sge::string& sge::dinput::input_device::name() const
{
	return _name;
}

#ifndef _MSC_VER
const std::size_t sge::dinput::input_device::buffer_size;
#endif
