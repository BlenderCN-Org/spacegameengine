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
#include <sge/opengl/common.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/convert_element_type.hpp>
#include <sge/opengl/vf/fp_actor.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/pos_actor.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/pos.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/text.hpp>


sge::opengl::vf::pos_actor::pos_actor(
	sge::opengl::vf::actor_parameters const &_param,
	sge::renderer::vf::dynamic::pos const &_pos
)
:
	sge::opengl::vf::fp_actor(
		_param,
		GL_VERTEX_ARRAY
	),
	format_(
		sge::opengl::vf::convert_element_type(
			_pos.type().element_type()
		)
	),
	elements_(
		static_cast<
			GLint
		>(
			_pos.type().element_count().get()
		)
	)
{
}

sge::opengl::vf::pos_actor::~pos_actor()
{
}

void
sge::opengl::vf::pos_actor::on_use(
	sge::opengl::vf::pointer const _src
) const
{
	::glVertexPointer(
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
		FCPPT_TEXT("glVertexPointer failed"),
		sge::renderer::exception
	)
}
