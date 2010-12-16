/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/dim.hpp>
#include <fcppt/math/box/basic_impl.hpp>

void
sge::renderer::sub_data(
	texture_ptr const _texture,
	image2d::view::const_object const &_view,
	texture_pos_type const &_pos
)
{
	scoped_texture_lock const lock(
		_texture,
		renderer::lock_rect(
			_pos,
			image2d::view::dim(
				_view
			)
		),
		renderer::lock_mode::writeonly
	);

	image2d::algorithm::copy_and_convert(
		_view,
		lock.value()
	);
}
