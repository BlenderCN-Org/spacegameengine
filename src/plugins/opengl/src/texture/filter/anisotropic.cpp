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


#include <sge/exception.hpp>
#include <sge/log/global.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/convert/anisotropic_mip_filter.hpp>
#include <sge/opengl/texture/filter/anisotropic.hpp>
#include <sge/opengl/texture/filter/anisotropy_context.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/texture/filter/anisotropic/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>


void
sge::opengl::texture::filter::anisotropic(
	sge::opengl::texture::binding const &_binding,
	sge::opengl::context::system::object &_system_context,
	sge::opengl::texture::type const _type,
	sge::renderer::texture::filter::anisotropic::object const &_filter
)
{
	sge::opengl::texture::funcs::parameter_int(
		_binding,
		_type,
		GL_TEXTURE_MAG_FILTER,
		GL_NEAREST
	);

	sge::opengl::texture::funcs::parameter_int(
		_binding,
		_type,
		GL_TEXTURE_MIN_FILTER,
		static_cast<
			GLint
		>(
			sge::opengl::texture::convert::anisotropic_mip_filter(
				_filter.mip()
			)
		)
	);

	sge::opengl::optional_enum const anisotropy_flag(
		sge::opengl::context::use<
			sge::opengl::texture::filter::anisotropy_context
		>(
			_system_context
		).anisotropy_flag()
	);

	if(
		!anisotropy_flag
	)
	{
		FCPPT_LOG_ERROR(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("anisotropic filtering is not supported!")
		);

		return;
	}

	try
	{
		sge::opengl::texture::funcs::parameter_int(
			_binding,
			_type,
			*anisotropy_flag,
			static_cast<
				GLint
			>(
				_filter.level().get()
			)
		);
	}
	catch(
		sge::exception const &
	)
	{
		FCPPT_LOG_ERROR(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("anisotropy level ")
				<< _filter.level()
				<< FCPPT_TEXT(" not supported!")
		);

		throw;
	}
}
