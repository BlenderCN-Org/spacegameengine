/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/convert/anisotropic_mip_filter.hpp>
#include <sge/opengl/state/core/sampler/actor.hpp>
#include <sge/opengl/state/core/sampler/actor_vector.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropic.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_context.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::core::sampler::actor_vector
sge::opengl::state::core::sampler::filter::anisotropic(
	sge::opengl::context::object &_context,
	sge::renderer::state::core::sampler::filter::anisotropic::parameters const &_filter
)
{
	return
		sge::opengl::state::core::sampler::actor_vector{
			sge::opengl::state::core::sampler::actor{
				std::bind(
					sge::opengl::texture::funcs::parameter_int,
					std::placeholders::_1,
					GL_TEXTURE_MAG_FILTER,
					GL_NEAREST
				)
			},
			sge::opengl::state::core::sampler::actor{
				std::bind(
					sge::opengl::texture::funcs::parameter_int,
					std::placeholders::_1,
					GL_TEXTURE_MIN_FILTER,
					fcppt::cast::to_signed(
						sge::opengl::state::convert::anisotropic_mip_filter(
							_filter.mip()
						)
					)
				)
			},
			sge::opengl::state::core::sampler::actor{
				std::bind(
					sge::opengl::texture::funcs::parameter_int,
					std::placeholders::_1,
					fcppt::optional_to_exception(
						sge::opengl::context::use<
							sge::opengl::state::core::sampler::filter::anisotropy_context
						>(
							_context,
							_context.info()
						).config(),
						[]{
							return
								sge::renderer::unsupported{
									FCPPT_TEXT("anisotropic filtering"),
									FCPPT_TEXT(""),
									FCPPT_TEXT("GL_EXT_texture_filter_anisotropic")
								};
						}
					).anisotropy_flag(),
					fcppt::cast::to_signed(
						_filter.level().get()
					)
				)
			}
		};
}
