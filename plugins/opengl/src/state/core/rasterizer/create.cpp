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


#include <sge/opengl/state/core/rasterizer/create.hpp>
#include <sge/opengl/state/core/rasterizer/make_actors.hpp>
#include <sge/opengl/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::state::core::rasterizer::object_unique_ptr
sge::opengl::state::core::rasterizer::create(
	sge::renderer::state::core::rasterizer::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::state::core::rasterizer::object
		>(
			fcppt::make_unique_ptr<
				sge::opengl::state::core::rasterizer::object
			>(
				sge::opengl::state::core::rasterizer::make_actors(
					_parameters
				)
			)
		);
}
