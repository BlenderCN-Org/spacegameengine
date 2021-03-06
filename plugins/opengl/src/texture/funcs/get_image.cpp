/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/funcs/get_image.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_void_ptr.hpp>


void
sge::opengl::texture::funcs::get_image(
	sge::opengl::texture::binding const &,
	sge::opengl::texture::buffer_type const _buffer_type,
	sge::opengl::color_order const _format,
	sge::opengl::color_base_type const _format_type,
	sge::renderer::raw_pointer const _dest,
	sge::renderer::texture::mipmap::level const _level
)
{
	sge::opengl::call(
		::glGetTexImage,
		_buffer_type.get(),
		fcppt::cast::to_signed(
			_level.get()
		),
		_format.get(),
		_format_type.get(),
		fcppt::cast::to_void_ptr(
			_dest
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGetTexImage failed"),
		sge::renderer::exception
	)
}
