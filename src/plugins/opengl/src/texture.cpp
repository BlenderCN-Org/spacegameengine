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


#include "../common.hpp"
#include "../texture.hpp"
#include "../error.hpp"
#include "../texture_functions.hpp"
#include "../basic_texture_impl.hpp"
#include "../vbo.hpp"
#include "../pbo.hpp"
#include "../color_convert.hpp"
#include <sge/renderer/scoped_lock.hpp>
#include <sge/renderer/make_image_view.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/math/rect_impl.hpp>

template class sge::ogl::basic_texture<sge::renderer::texture>;

namespace
{

const GLenum texture_type = GL_TEXTURE_2D;

}

sge::ogl::texture::texture(
	dim_type const &d,
	renderer::color_format::type const format_,
	renderer::filter_args const &filter,
	resource_flag_type const flags)
: detail::texture_base(
	filter,
	flags,
	texture_type,
	format_),
  dim_(d)
{
	set_texture(0);	
}

const sge::ogl::texture::dim_type
sge::ogl::texture::dim() const
{
	return dim_;
}

sge::renderer::image_view const
sge::ogl::texture::lock(
	renderer::lock_rect const &r,
	lock_flag_type const lmode)
{
	lock_me(
		r,
		convert_lock_method(
			lmode));
	return view();
}

sge::renderer::const_image_view const
sge::ogl::texture::lock(
	renderer::lock_rect const &l) const
{
	lock_me(
		l,
		lock_method::readonly);
	return view();
}

#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <ostream>

void sge::ogl::texture::unlock() const
{
	cerr << SGE_TEXT("unlock\n");
	pre_unlock();
	if(lock_flag_write(lock_mode()))
	{
		if(!lock_rect_)
			set_texture(
				write_buffer());
		else
			set_texture_rect(
				type(),
				format(),
				format_type(),
				filter(),
				dim(),
				*lock_rect_,
				write_buffer());
	}
	do_unlock();
}

void sge::ogl::texture::lock_me(
	renderer::lock_rect const &l,
	lock_method::type const method) const
{
	bool const must_read = lock_flag_read(method);

	// if we must read we have to lock the whole texture
	// and set the lock size, the offset and the pitch accordingly
	do_lock(
		method,
		must_read
			? content()
			: l.area(),
		must_read
			? l.left() + l.top() * dim().w()
			: 0,
		must_read
			? dim().w() - l.dim().w()
			: 0);
	if(must_read)
		get_tex_image(
			format(),
			format_type(),
			read_buffer());

	post_lock();

	if(l == rect())
	{
		cerr << SGE_TEXT("lock all: ") << dim() << SGE_TEXT("\n");
		lock_rect_.reset();
	}
	else
	{
		cerr << SGE_TEXT("lock part: ") << l << SGE_TEXT("\n");
		lock_rect_ = l;
	}
}

sge::renderer::image_view const
sge::ogl::texture::view()
{
	return renderer::make_image_view(
		write_buffer(),
		lock_dim(),
		color_convert(
			format(),
			format_type()));
}

sge::renderer::const_image_view const
sge::ogl::texture::view() const
{
	return renderer::make_image_view(
		static_cast<const_pointer>(
			write_buffer()),
		lock_dim(),
		color_convert(
			format(),
			format_type()));
}

sge::ogl::texture::dim_type const
sge::ogl::texture::lock_dim() const
{
	return lock_rect_
		? lock_rect_->dim()
		: dim();
}

void sge::ogl::texture::set_texture(
	const_pointer const p) const
{
	pre_setdata();
	ogl::set_texture(
		type(),
		format(),
		format_type(),
		filter(),
		dim(),
		p);
}
