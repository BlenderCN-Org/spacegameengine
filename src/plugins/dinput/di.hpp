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


#ifndef SGE_DINPUT_DI_HPP_INCLUDED
#define SGE_DINPUT_DI_HPP_INCLUDED

#include "../../shared_ptr.hpp"
#include "../../com_deleter.hpp"

#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace sge
{
namespace dinput
{

typedef IDirectInput8       direct_input;
typedef IDirectInputDevice8 direct_input_device;
typedef shared_ptr<direct_input,com_deleter> dinput_ptr;
typedef shared_ptr<direct_input_device,com_deleter> dinput_device_ptr;

}
}

#endif
