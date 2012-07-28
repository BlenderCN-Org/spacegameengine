/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_RENDERER_COLOR_BUFFER_INSTANTIATE_CONST_BASIC_SCOPED_LOCK_HPP_INCLUDED
#define SGE_SRC_RENDERER_COLOR_BUFFER_INSTANTIATE_CONST_BASIC_SCOPED_LOCK_HPP_INCLUDED

#include <sge/src/export_class_instantiation.hpp>
#include <sge/src/renderer/color_buffer/const_basic_scoped_lock_impl.hpp>


#define SGE_RENDERER_COLOR_BUFFER_INSTANTIATE_CONST_BASIC_SCOPED_LOCK(\
	buffer\
)\
template \
class \
SGE_EXPORT_CLASS_INSTANTIATION \
sge::renderer::color_buffer::const_basic_scoped_lock<\
	buffer\
>

#endif
