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


#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/renderer.hpp>
#include <sge/src/cegui/scoped_render_context.hpp>


sge::cegui::scoped_render_context::scoped_render_context(
	sge::cegui::renderer &_renderer,
	sge::renderer::context::ffp &_render_context
)
:
	renderer_(
		_renderer
	)
{
	renderer_.render_context(
		sge::cegui::optional_render_context_ref(
			_render_context
		)
	);
}

sge::cegui::scoped_render_context::~scoped_render_context()
{
	renderer_.render_context(
		sge::cegui::optional_render_context_ref()
	);
}
