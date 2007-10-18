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


#ifndef SGE_D3D_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_D3D_VERTEX_FORMAT_HPP_INCLUDED

#include "../../renderer/vertex_buffer.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
namespace d3d
{

class vertex_format {
public:
	vertex_format(d3d_device_ptr device, const sge::vertex_format& format);
	d3d_vertex_declaration_ptr vertex_declaration() const { return _vertex_declaration; }
	const offset_info& get_offset_info() const { return oi; }
	DWORD fvf() const { return _fvf; }
	vertex_size stride() const { return _stride; }
private:
	d3d_vertex_declaration_ptr _vertex_declaration;
	offset_info                oi;
	DWORD                      _fvf;
	vertex_size                _stride;
};

}
}

#endif
