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


#include <sge/texture/atlasing.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/texture_util.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <sge/renderer/image_view_dim.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/power.hpp>

bool sge::texture::need_atlasing(
	renderer::size_type const s)
{
	return !math::is_power_of_2(s);
}

bool sge::texture::need_atlasing(
	renderer::dim_type const &dim)
{
	return !math::is_power_of_2(dim);
}

sge::renderer::size_type
sge::texture::atlased_bound(
	renderer::size_type const s)
{
	return math::is_power_of_2(s)
		? s
		: math::next_pow_2(s);
}

sge::renderer::dim_type const
sge::texture::atlased_bounds(
	renderer::dim_type const &dim)
{
	return renderer::dim_type(
		atlased_bound(dim.w()),
		atlased_bound(dim.h()));
}

sge::renderer::size_type
sge::texture::atlased_gap()
{
	return 1;
}

sge::renderer::size_type
sge::texture::atlased_size(
	renderer::size_type const s,
	bool const force_atlasing)
{
	return need_atlasing(s) || force_atlasing
		? s + 2 * atlased_gap()
		: s;
}

sge::renderer::dim_type const
sge::texture::atlased_size(
	renderer::dim_type const &dim,
	bool const force_atlasing)
{
	return renderer::dim_type(
		atlased_size(
			dim.w(),
			force_atlasing),
		atlased_size(
			dim.h(),
			force_atlasing));
}

sge::renderer::dim_type const
sge::texture::atlased_texture_dim(
	renderer::device_ptr const rend)
{
	renderer::size_type const max_size = rend->get_caps().max_tex_size;
	return renderer::dim_type(max_size, max_size);
}

sge::renderer::texture_ptr const
sge::texture::atlased_texture(
	renderer::device_ptr const rend,
	renderer::filter_args const &filter)
{
	return rend->create_texture(
		atlased_texture_dim(rend),
		renderer::color_format::rgba8, // TODO: add a common format
		filter,
		renderer::resource_flags::none);
}

sge::renderer::lock_rect const
sge::texture::inner_atlased_rect(
	renderer::lock_rect outer,
	bool const need_atlasing_w,
	bool const need_atlasing_h)
{
	if(need_atlasing_w)
	{
		++outer.left();
		--outer.right();
	}
	if(need_atlasing_h)
	{
		++outer.top();
		--outer.bottom();
	}
	return outer;
}

void sge::texture::atlas_w(
	renderer::texture_ptr const tex,
	renderer::const_image_view const &src,
	renderer::lock_rect const &outer_area)
{
	// FIXME: use a gil image here
	/*typedef std::vector<renderer::texture::value_type> pixel_vector;
	pixel_vector height_pixels(outer_area().h());

	height_pixels.front() = *src;
	for(pixel_vector::size_type h = 1; h < height_pixels.size() - 1; ++h)
		height_pixels[h] = *(src + area().w() * h);
	height_pixels.back() = *(src + area().w() * (area().h() - 1));

	my_texture()->set_data(
		height_pixels.data(),
		renderer::lock_rect(
			outer_area().left(),
			outer_area().top(),
			outer_area().left() + 1,
			outer_area().bottom()));

	height_pixels.front() = *(src + area().w() - 1); 
	for(pixel_vector::size_type h = 1; h < height_pixels.size() - 1; ++h)
		height_pixels[h] = *(src + area().w() * (h + 1) - 1);
	height_pixels.back() = *(src + area().w() * area().h() - 1);

	my_texture()->set_data(
		height_pixels.data(),
	        renderer::lock_rect(
			outer_area().right() - 1,
			outer_area().top(),
			outer_area().right(),
			outer_area().bottom()));*/
}
	
void sge::texture::atlas_h(
	renderer::texture_ptr const tex,
	renderer::const_image_view const &src,
	renderer::lock_rect const &outer_area)
{
	renderer::dim_type const dim(
		renderer::image_view_dim(
			src));

	renderer::sub_data(
		tex,
		renderer::subimage_view(
			src,
			renderer::lock_rect(
				0,
				0,
				dim.w(),
				1)),
		renderer::texture_pos_type(
			outer_area.left() + 1,
			outer_area.top()));
	
	renderer::sub_data(
		tex,
		renderer::subimage_view(
			src,
			renderer::lock_rect(
				0,
				dim.h() - 1,
				dim.w(),
				dim.h())),
		renderer::texture_pos_type(
			outer_area.left() + 1,
			outer_area.bottom() - 1));
}
