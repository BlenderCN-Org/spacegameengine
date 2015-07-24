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
#include <sge/opengl/occlusion_query/begin.hpp>
#include <sge/opengl/occlusion_query/config.hpp>
#include <sge/opengl/occlusion_query/end.hpp>
#include <sge/opengl/occlusion_query/get_object_int.hpp>
#include <sge/opengl/occlusion_query/get_object_uint.hpp>
#include <sge/opengl/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/blocking_wait.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/optional_pixel_count.hpp>
#include <sge/renderer/occlusion_query/pixel_count.hpp>


sge::opengl::occlusion_query::object::object(
	sge::opengl::occlusion_query::config const &_config
)
:
	sge::renderer::occlusion_query::object(),
	config_(
		_config
	),
	holder_(
		config_
	)
{
}

sge::opengl::occlusion_query::object::~object()
{
}

void
sge::opengl::occlusion_query::object::begin()
{
	sge::opengl::occlusion_query::begin(
		config_,
		holder_.id()
	);
}

void
sge::opengl::occlusion_query::object::end()
{
	sge::opengl::occlusion_query::end(
		config_
	);
}

sge::renderer::occlusion_query::optional_pixel_count const
sge::opengl::occlusion_query::object::result(
	sge::renderer::occlusion_query::blocking_wait const _block
) const
{
	return
		(
			sge::opengl::occlusion_query::get_object_int(
				config_,
				holder_.id(),
				config_.query_result_available()
			)
			== GL_FALSE
			&&
			!_block.get()
		)
		?
			sge::renderer::occlusion_query::optional_pixel_count()
		:
			sge::renderer::occlusion_query::optional_pixel_count(
				sge::renderer::occlusion_query::pixel_count(
					sge::opengl::occlusion_query::get_object_uint(
						config_,
						holder_.id(),
						config_.query_result()
					)
				)
			)
		;
}
