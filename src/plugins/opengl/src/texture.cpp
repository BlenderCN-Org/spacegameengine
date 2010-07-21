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


#include "../common.hpp"
#include "../texture.hpp"
#include "../basic_texture_impl.hpp"
#include "../color_convert.hpp"
#include "../texfuncs/set.hpp"
#include "../texfuncs/set_rect.hpp"
#include "../texfuncs/get_image.hpp"
#include <sge/image/view/make.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

template class sge::opengl::basic_texture<sge::renderer::texture>;

namespace
{

GLenum const texture_type = GL_TEXTURE_2D;

}

sge::opengl::texture::texture(
	context::object &_context,
	dim_type const &_dim,
	image::color::format::type const _format,
	renderer::filter::texture const &_filter,
	renderer::resource_flags_field const &_flags,
	optional_type const _type
)
:
	detail::texture_base(
		_context,
		_filter,
		_flags,
		_type
		?
			*_type
		:
			texture_type,
		_format
	),
	dim_(_dim)
{
	pre_setdata();

	texfuncs::set(
		_context,
		type(),
		format(),
		format_type(),
		filter(),
		dim(),
		0
	);
}

sge::opengl::texture::dim_type const
sge::opengl::texture::dim() const
{
	return dim_;
}

sge::image::view::object const
sge::opengl::texture::lock(
	renderer::lock_rect const &r,
	renderer::lock_mode::type const lmode
)
{
	lock_me(
		r,
		convert_lock_method(
			lmode
		)
	);

	return view();
}

sge::image::view::const_object const
sge::opengl::texture::lock(
	renderer::lock_rect const &l
) const
{
	lock_me(
		l,
		lock_method::readonly
	);

	return view();
}

void
sge::opengl::texture::unlock() const
{
	pre_unlock();

	if(lock_flag_write(lock_mode()))
	{
		bind_me();

		renderer::lock_rect const lr(
			lock_rect_
				? *lock_rect_
				: renderer::lock_rect(
					renderer::lock_rect::vector::null(),
					dim()
				)
		);

		texfuncs::set_rect(
			context(),
			type(),
			format(),
			format_type(),
			dim(),
			lr,
			write_buffer()
		);
	}

	do_unlock();
}

void
sge::opengl::texture::lock_me(
	renderer::lock_rect const &l,
	lock_method::type const method
) const
{
	if(
		l.right() > dim().w()
		|| l.bottom() > dim().h()
	)
		throw exception(
			(
				fcppt::format(
					FCPPT_TEXT("ogl: lock_rect (%1%) out of range! dim is %2%!")
				)
				% l
				% dim()
			).str()
		);

	bool const must_read = lock_flag_read(method);

	// if we must read we have to lock the whole texture
	// and set the lock size, the offset and the pitch accordingly
	if(must_read)
		do_lock(
			method,
			l.area(),
			l.left() + l.top() * dim().w(),
			dim().w() - l.dimension().w(),
			l.dimension().w()
		);
	else
		do_lock(
			method,
			l.area(),
			0,
			0,
			0
		);

	if(must_read)
		texfuncs::get_image(
			format(),
			format_type(),
			read_buffer()
		);

	post_lock();

	if(l == rect())
		lock_rect_.reset();
	else
		lock_rect_ = l;
}

sge::image::view::object const
sge::opengl::texture::view()
{
	return image::view::make(
		real_write_buffer(),
		lock_dim(),
		color_convert(
			format(),
			format_type()
		),
		image::view::optional_pitch()
	);
}

sge::image::view::const_object const
sge::opengl::texture::view() const
{
	return image::view::make(
		static_cast<
			const_pointer
		>(
			real_read_buffer()
		),
		lock_dim(),
		color_convert(
			format(),
			format_type()
		),
		image::view::optional_pitch()
	);
}

sge::opengl::texture::dim_type const
sge::opengl::texture::lock_dim() const
{
	return lock_rect_
		? lock_rect_->dimension()
		: dim();
}
