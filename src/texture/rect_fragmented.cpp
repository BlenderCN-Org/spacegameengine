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


#include <sge/image/color/format.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/part_unique_ptr.hpp>
#include <sge/texture/rect_fragmented.hpp>
#include <sge/texture/atlasing/create.hpp>
#include <sge/texture/atlasing/size.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/move.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::texture::rect_fragmented::rect_fragmented(
	renderer::device &_rend,
	image::color::format::type const _format,
	renderer::texture::mipmap::object const &_mipmap,
	renderer::dim2 const &_initial_size
)
:
	cur_x_(0),
	cur_y_(0),
	cur_height_(0),
	tex_(
		atlasing::create(
			_rend,
			_format,
			_mipmap,
			_initial_size
		)
	),
	texture_count_(0)
{
}

sge::texture::rect_fragmented::~rect_fragmented()
{
}

sge::texture::part_unique_ptr
sge::texture::rect_fragmented::consume_fragment(
	renderer::dim2 const &_size
)
{
	renderer::texture::planar::dim const atlased_dim(
		atlasing::size(
			_size,
			true
		)
	);

	// if there is no space left for the requested height
	if(
		cur_y_ + _size.h() >= tex_->size().h()
	)
		return texture::part_unique_ptr();

	// if the current line is full advance to the next
	if(
		cur_x_ + _size.w() >= tex_->size().w()
	)
	{
		cur_x_ = 0;
		cur_y_ += cur_height_;
		cur_height_ = 0;
	}

	if(
		cur_y_ + _size.h() >= tex_->size().h()
	)
		return texture::part_unique_ptr();

	texture::part_unique_ptr ret(
		fcppt::make_unique_ptr<
			texture::part_fragmented
		>(
			renderer::lock_rect(
				renderer::lock_rect::vector(
					cur_x_,
					cur_y_
				),
				atlased_dim
			),
			fcppt::ref(
				*this
			),
			true,
			true
		)
	);

	cur_x_ += _size.w() + 1;

	cur_height_ = std::max(cur_height_, _size.h());

	++texture_count_;

	return
		fcppt::move(
			ret
		);
}

void
sge::texture::rect_fragmented::return_fragment(
	part const &
)
{
	--texture_count_;
}

sge::renderer::texture::planar &
sge::texture::rect_fragmented::texture()
{
	return *tex_;
}

sge::renderer::texture::planar const &
sge::texture::rect_fragmented::texture() const
{
	return *tex_;
}

bool
sge::texture::rect_fragmented::repeatable() const
{
	return false;
}

bool
sge::texture::rect_fragmented::empty() const
{
	return texture_count_ == 0u;
}
