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


#ifndef SGE_WINDOWS_CHOOSE_PIXEL_FORMAT_HPP_INCLUDED
#define SGE_WINDOWS_CHOOSE_PIXEL_FORMAT_HPP_INCLUDED

#include "windows.hpp"

namespace sge
{
namespace windows
{

class device_context;

// TODO: maybe add the remaining parameters as well?
int choose_pixel_format(
	device_context const &,
	DWORD flags,
	BYTE pixel_type,
	BYTE depth,
	BYTE depth_buffer,
	BYTE stencil_buffer);

}
}

#endif
