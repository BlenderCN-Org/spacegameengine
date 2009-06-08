/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/sub_data.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/dim.hpp>
#include <sge/math/rect/basic_impl.hpp>

void sge::renderer::sub_data(
	texture_ptr const tex,
	image::view::const_object const &view,
	texture_pos_type const &p)
{
	scoped_texture_lock const lock_(
		tex,
		lock_rect(
			p,
			image::view::dim(view)
		),
		lock_flags::writeonly
	);

	image::algorithm::copy_and_convert(
		view,
		lock_.value()
	);
}
