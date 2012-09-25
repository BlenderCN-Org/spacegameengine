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


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/rasterizer/object_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/scoped.hpp>


sge::renderer::state::core::rasterizer::scoped::scoped(
	sge::renderer::context::core &_context,
	sge::renderer::state::core::rasterizer::object const &_object
)
:
	context_(
		_context
	)
{
	context_.rasterizer_state(
		sge::renderer::state::core::rasterizer::const_optional_object_ref(
			_object
		)
	);
}

sge::renderer::state::core::rasterizer::scoped::~scoped()
{
	context_.rasterizer_state(
		sge::renderer::state::core::rasterizer::const_optional_object_ref()
	);
}
