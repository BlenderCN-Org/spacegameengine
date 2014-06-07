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
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/convert_element_type.hpp>
#include <sge/opengl/vf/fp_actor.hpp>
#include <sge/opengl/vf/normal_actor.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/normal.hpp>
#include <fcppt/text.hpp>


sge::opengl::vf::normal_actor::normal_actor(
	sge::opengl::vf::actor_parameters const &_param,
	renderer::vf::dynamic::normal const &_normal
)
:
	sge::opengl::vf::fp_actor(
		_param,
		GL_NORMAL_ARRAY
	),
	format_(
		sge::opengl::vf::convert_element_type(
			_normal.element_type()
		)
	)
{
}

sge::opengl::vf::normal_actor::~normal_actor()
{
}

void
sge::opengl::vf::normal_actor::on_use(
	sge::opengl::vf::pointer const _src
) const
{
	::glNormalPointer(
		format_,
		static_cast<
			GLsizei
		>(
			this->stride().get()
		),
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glNormalPointer failed"),
		sge::renderer::exception
	)
}
