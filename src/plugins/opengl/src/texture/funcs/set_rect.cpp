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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/range_check.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/pbo_context.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/funcs/set_rect.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/format.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/output.hpp>


void
sge::opengl::texture::funcs::set_rect(
	sge::opengl::texture::binding const &,
	sge::opengl::context::system::object &_system_context,
	sge::opengl::texture::type const _type,
	sge::opengl::color_format const _format,
	sge::opengl::color_format_type const _format_type,
	sge::renderer::texture::mipmap::level const _level,
	sge::renderer::dim2 const &_dim,
	sge::renderer::lock_rect const &_lock_rect,
	sge::renderer::const_raw_pointer const _src
)
{
	if(
		_src == fcppt::null_ptr()
		&&
		!sge::opengl::context::use<
			sge::opengl::buffer::pbo_context
		>(
			_system_context
		)
		.impl()
		.hardware_supported()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("OpenGL: Texture source is 0 although no PBO is bound!")
		);

	if(
		!sge::opengl::range_check(
			_dim,
			_lock_rect
		)
	)
		throw sge::renderer::exception(
			(
				fcppt::format(
					FCPPT_TEXT("rect for setting a texture is out of range (rect=%1%, dim=%2%)!")
				)
				% _lock_rect
				% _dim
			)
			.str()
		);

	::glTexSubImage2D(
		_type.get(),
		static_cast<
			GLint
		>(
			_level.get()
		),
		static_cast<
			GLint
		>(
			_lock_rect.left()
		),
		static_cast<
			GLint
		>(
			_lock_rect.top()
		),
		static_cast<
			GLsizei
		>(
			_lock_rect.w()
		),
		static_cast<
			GLsizei
		>(
			_lock_rect.h()
		),
		_format.get(),
		_format_type.get(),
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		(
			fcppt::format(
				FCPPT_TEXT("glTexSubImage2D with rect (rect=%1%, dim=%2%) failed")
			)
			% _lock_rect
			% _dim
		).str(),
		sge::renderer::exception
	)
}
