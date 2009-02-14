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


#include "../index_buffer.hpp"
#include "../vbo.hpp"
#include "../instantiate_basic_buffer.hpp"
#include <sge/renderer/index/view_16.hpp>
#include <sge/renderer/index/view_32.hpp>
#include <sge/typeswitch.hpp>

namespace
{

template<
	typename T
>
struct traits;

template<>
struct traits<
	sge::uint16
> {
	static GLenum const gl_format = GL_UNSIGNED_SHORT;
	static sge::renderer::index::format::type const format = sge::renderer::index::format::i16;
	typedef sge::renderer::index::view_16 view;
	typedef sge::renderer::index::const_view_16 const_view;
};

template<>
struct traits<
	sge::uint32
> {
	static GLenum const gl_format = GL_UNSIGNED_INT;
	static sge::renderer::index::format::type const format = sge::renderer::index::format::i32;
	typedef sge::renderer::index::view_32 view;
	typedef sge::renderer::index::const_view_32 const_view;
};

}

template<
	typename T
>
sge::ogl::index_buffer<T>::index_buffer(
	size_type const sz,
	resource_flag_type const flags)
:
	buf(
		sz,
		sizeof(T),
		flags,
		0)
{}

template<
	typename T
>
GLenum
sge::ogl::index_buffer<T>::gl_format() const
{
	return traits<
		T
	>::gl_format;
}

template<
	typename T
>
void *
sge::ogl::index_buffer<T>::buffer_offset(
	size_type const sz) const
{
	return buf.buffer_offset(
		sz);
}

template<
	typename T
>
void
sge::ogl::index_buffer<T>::bind_me() const
{
	buf.bind_me();
}

template<
	typename T
>
typename sge::ogl::index_buffer<T>::view_type const
sge::ogl::index_buffer<T>::lock(
	lock_flag_type const flags,
	size_type const offset,
	size_type const range)
{
	buf.lock(
		convert_lock_method(
			flags),
		offset,
		range);
	
	return typename traits<T>::view(
		buf.data(),
		buf.lock_size());
}

template<
	typename T
>
typename sge::ogl::index_buffer<T>::const_view_type const
sge::ogl::index_buffer<T>::lock(
	size_type const offset,
	size_type const range) const
{
	buf.lock(
		lock_method::readonly,
		offset,
		range);

	return typename traits<T>::const_view(
		buf.data(),
		buf.lock_size());
}

template<
	typename T
>
void
sge::ogl::index_buffer<T>::unlock() const
{
	buf.unlock();
}

template<
	typename T
>
typename sge::ogl::index_buffer<T>::size_type
sge::ogl::index_buffer<T>::size() const
{
	return buf.size();
}

template<
	typename T
>
typename sge::ogl::index_buffer<T>::resource_flag_type
sge::ogl::index_buffer<T>::flags() const
{
	return buf.flags();
}

template<
	typename T
>
sge::renderer::index::format::type
sge::ogl::index_buffer<T>::format() const
{
	return traits<
		T
	>::format;
}

#define SGE_OPENGL_INSTANTIATE_INDEX_BUFFER(t) \
template class sge::ogl::index_buffer<t>; \
template class sge::ogl::basic_buffer<\
	sge::ogl::index_buffer_type,\
	sge::ogl::vb_ib_vbo_impl,\
	t\
>;

SGE_OPENGL_INSTANTIATE_INDEX_BUFFER(sge::uint16)
SGE_OPENGL_INSTANTIATE_INDEX_BUFFER(sge::uint32)

#undef SGE_OPENGL_INSTANTIATE_INDEX_BUFFER
