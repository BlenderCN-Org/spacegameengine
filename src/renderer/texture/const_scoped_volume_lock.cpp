/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "const_basic_scoped_lock_impl.hpp"
#include <sge/renderer/texture/const_scoped_volume_lock.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/const_volume_ptr.hpp>
#include <sge/renderer/lock_box.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <fcppt/export_symbol.hpp>

template class
FCPPT_EXPORT_SYMBOL
sge::renderer::texture::const_basic_scoped_lock<
	sge::renderer::texture::const_volume_ptr,
	sge::renderer::lock_box,
	sge::image3d::view::const_object
>;
