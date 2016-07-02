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


#include <sge/opengl/common.hpp>
#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/get_int.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/texture/multi_config.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/optional_multi_config.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::opengl::texture::multi_context::multi_context(
	sge::opengl::info::context const &_info
)
:
	sge::opengl::context::base(),
	config_(
		sge::opengl::info::version_at_least(
			_info.version(),
			sge::opengl::info::major_version{
				1u
			},
			sge::opengl::info::minor_version{
				3u
			}
		)
		?
			sge::opengl::texture::optional_multi_config(
				sge::opengl::texture::multi_config(
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLACTIVETEXTUREPROC
						>(
							_info.load_function(
								"glActiveTexture"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							sge::opengl::texture::multi_config::gl_client_active_texture_proc
						>(
							_info.load_function(
								"glClientActiveTexture"
							)
						)
					),
					fcppt::strong_typedef_construct_cast<
						sge::renderer::caps::texture_stages,
						fcppt::cast::static_cast_fun
					>(
						std::min(
							sge::opengl::get_int(
								GL_MAX_TEXTURE_COORDS
							),
							sge::opengl::get_int(
								GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
							)
						)
					)
				)
			)
		:
			sge::opengl::info::extension_supported(
				_info.extensions(),
				sge::opengl::info::extension{
					"GL_ARB_multitexture"
				}
			)
			?
				sge::opengl::texture::optional_multi_config(
					sge::opengl::texture::multi_config(
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLACTIVETEXTUREPROC
							>(
								_info.load_function(
									"glActiveTextureARB"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								sge::opengl::texture::multi_config::gl_client_active_texture_proc
							>(
								_info.load_function(
									"glClientActiveTextureARB"
								)
							)
						),
						fcppt::strong_typedef_construct_cast<
							sge::renderer::caps::texture_stages,
							fcppt::cast::static_cast_fun
						>(
							std::min(
								sge::opengl::get_int(
									GL_MAX_TEXTURE_COORDS_ARB
								),
								sge::opengl::get_int(
									GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB
								)
							)
						)
					)
				)
			:
				sge::opengl::texture::optional_multi_config()
	)
{
}

sge::opengl::texture::multi_context::~multi_context()
{
}

sge::opengl::texture::optional_multi_config const &
sge::opengl::texture::multi_context::config() const
{
	return
		config_;
}

sge::opengl::context::id const
sge::opengl::texture::multi_context::static_id(
	sge::opengl::context::make_id()
);