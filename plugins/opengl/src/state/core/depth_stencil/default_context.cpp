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


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/core/depth_stencil/default_context.hpp>
#include <sge/opengl/state/core/depth_stencil/make_actors.hpp>
#include <sge/opengl/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/default.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::state::core::depth_stencil::default_context::default_context(
	sge::opengl::state::core::depth_stencil::default_context::parameter _context
)
:
	sge::opengl::context::base(),
	default_state_(
		fcppt::make_unique_ptr<
			sge::opengl::state::core::depth_stencil::object
		>(
			sge::opengl::state::core::depth_stencil::make_actors(
				_context,
				sge::renderer::state::core::depth_stencil::default_()
			)
		)
	)
{
}

sge::opengl::state::core::depth_stencil::default_context::~default_context()
{
}

sge::opengl::state::core::depth_stencil::object const &
sge::opengl::state::core::depth_stencil::default_context::default_state() const
{
	return
		*default_state_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::state::core::depth_stencil::default_context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
