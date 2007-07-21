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


#ifndef SGE_OGL_CONVERSION_HPP_INCLUDED
#define SGE_OGL_CONVERSION_HPP_INCLUDED

#include "../../renderer/types.hpp"
#include "common.hpp"

namespace sge
{
namespace ogl
{

template<typename D, typename S> D convert_cast(const S&);
template<> GLenum convert_cast(const indexed_primitive_type&);
template<> GLenum convert_cast(const nonindexed_primitive_type&);
template<> GLenum convert_cast(const bool_state&);
template<> GLenum convert_cast(const min_filter_value&);
template<> GLenum convert_cast(const mag_filter_value&);
template<> GLenum convert_cast(const cube_side&);
template<> GLenum convert_cast(const cull_mode&);
GLuint convert_lock_flags(lock_flag_t);
GLuint convert_resource_flags(resource_flag_t);
GLenum convert_fog_float_state(const float_state&);
GLint convert_fog_int_value(const int_type&);

}
}

#endif

