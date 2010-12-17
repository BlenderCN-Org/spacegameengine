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


#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/texture.hpp>

sge::renderer::scoped_texture_lock::scoped_texture_lock(
	texture_ptr const _tex,
	lock_mode::type const _flags
)
:
	tex_(_tex),
	view_(
		tex_->lock(
			_flags
		)
	)
{}

sge::renderer::scoped_texture_lock::scoped_texture_lock(
	texture_ptr const _tex,
	lock_rect const &_rect,
	lock_mode::type const _flags
)
:
	tex_(_tex),
	view_(
		tex_->lock(
			_rect,
			_flags
		)
	)
{}

sge::image2d::view::object const
sge::renderer::scoped_texture_lock::value() const
{
	return view_;
}

sge::renderer::scoped_texture_lock::~scoped_texture_lock()
{
	tex_->unlock();
}
