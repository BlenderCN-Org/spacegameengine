/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../anisotropic_filter.hpp"
#include "../parameter_int.hpp"
#include "../../convert/anisotropic_mip_filter.hpp"
#include "../../context.hpp"
#include "../../../context/use.hpp"
#include "../../../common.hpp"
#include <sge/renderer/texture/filter/anisotropic/object.hpp>
#include <sge/log/global.hpp>
#include <sge/exception.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::texture::funcs::anisotropic_filter(
	opengl::context::object &_context,
	texture::scoped_work_bind const &_scoped_work,
	texture::type const _type,
	renderer::texture::filter::anisotropic::object const &_filter
)
{
	funcs::parameter_int(
		_scoped_work,
		_type,
		GL_TEXTURE_MAG_FILTER,
		GL_NEAREST
	);

	funcs::parameter_int(
		_scoped_work,
		_type,
		GL_TEXTURE_MIN_FILTER,
		static_cast<
			GLint
		>(
			texture::convert::anisotropic_mip_filter(
				_filter.mip()
			)
		)
	);

	texture::context const &context(
		opengl::context::use<
			texture::context
		>(
			_context
		)
	);

	if(
		!context.anisotropic_filter_supported()
	)
	{
		FCPPT_LOG_ERROR(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("anisotropic filtering is not supported!")
		);

		return;
	}

	try
	{
		funcs::parameter_int(
			_scoped_work,
			_type,
			context.anisotropy_flag(),
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
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("anisotropy level ")
				<< _filter.level()
				<< FCPPT_TEXT(" not supported!")
		);

		throw;
	}
}