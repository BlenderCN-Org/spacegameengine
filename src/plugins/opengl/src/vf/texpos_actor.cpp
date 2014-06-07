/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/funcs/set_client_level.hpp>
#include <sge/opengl/vf/actor_parameters.hpp>
#include <sge/opengl/vf/client_state_combiner.hpp>
#include <sge/opengl/vf/convert_element_type.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/texpos_actor.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>


sge::opengl::vf::texpos_actor::texpos_actor(
	sge::opengl::vf::actor_parameters const &_param,
	sge::renderer::vf::dynamic::texpos const &_element
)
:
	sge::opengl::vf::pointer_actor(
		_param
	),
	system_context_(
		_param.system_context()
	),
	elements_(
		static_cast<
			GLint
		>(
			_element.type().element_count().get()
		)
	),
	format_(
		vf::convert_element_type(
			_element.type().element_type()
		)
	),
	index_(
		_element.index().get()
	)
{
	sge::opengl::texture::multi_context &texture_context(
		sge::opengl::context::use<
			sge::opengl::texture::multi_context
		>(
			system_context_
		)
	);

	if(
		!texture_context.is_supported()
		&& index_.get() != 0
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("multiple texture coordinates are not supported!")
		);
	else if(
		index_.get()
		>=
		texture_context.max_level().get()
	)
		throw sge::renderer::exception(
			(
				fcppt::format(
					FCPPT_TEXT("opengl texture coordinates exceeded: Allowed are %1%.")
				)
				% texture_context.max_level()
			).str()
		);
}

sge::opengl::vf::texpos_actor::~texpos_actor()
{
}

void
sge::opengl::vf::texpos_actor::operator()(
	sge::opengl::vf::client_state_combiner &_combiner,
	sge::opengl::vf::pointer const _src
) const
{
	_combiner.enable_texture(
		index_
	);

	sge::opengl::texture::funcs::set_client_level(
		system_context_,
		index_
	);

	::glTexCoordPointer(
		elements_,
		format_,
		static_cast<
			GLsizei
		>(
			this->stride().get()
		),
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glTexCoordPointer failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::vf::texpos_actor::unuse(
	sge::opengl::vf::client_state_combiner &_combiner
) const
{
	_combiner.disable_texture(
		index_
	);
}
