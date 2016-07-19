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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/multi_config.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/convert/level.hpp>
#include <sge/opengl/texture/funcs/set_client_level.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/format.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/maybe.hpp>


void
sge::opengl::texture::funcs::set_client_level(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context,
	sge::renderer::texture::stage const _stage
)
{
	// TODO: Should we require multi_config as an argument here?

	fcppt::optional::maybe(
		sge::opengl::context::use<
			sge::opengl::texture::multi_context
		>(
			_context,
			_context.info()
		).config(),
		[
			&_log,
			_stage
		]{
			if(
				_stage.get()
				==
				0u
			)
				return;

			FCPPT_LOG_ERROR(
				_log,
				fcppt::log::_
					<< FCPPT_TEXT("Tried to set texture coordinates for stage ")
					<< _stage
					<< FCPPT_TEXT(" but opengl does not support it.")
			);
		},
		[
			_stage
		](
			sge::opengl::texture::multi_config const &_config
		)
		{
			_config.client_active_texture()(
				sge::opengl::texture::convert::level(
					_stage
				)
			);

			SGE_OPENGL_CHECK_STATE(
				(
					fcppt::format(
						FCPPT_TEXT("glClientActiveTexture failed for stage %1%")
					)
					% _stage
				).str(),
				sge::renderer::exception
			)
		}
	);
}
