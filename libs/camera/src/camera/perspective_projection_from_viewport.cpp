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


#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/renderer/projection/aspect.hpp>
#include <sge/renderer/projection/perspective_af.hpp>
#include <sge/renderer/target/aspect_from_viewport.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::camera::perspective_projection_from_viewport::perspective_projection_from_viewport(
	sge::camera::has_mutable_projection &_camera,
	sge::viewport::manager &_viewport_manager,
	sge::renderer::projection::near const _near,
	sge::renderer::projection::far const _far,
	sge::renderer::projection::fov const _fov
)
:
	camera_(
		_camera
	),
	near_(
		_near
	),
	far_(
		_far
	),
	fov_(
		_fov
	),
	viewport_callback_connection_(
		_viewport_manager.manage_callback(
			sge::viewport::manage_callback{
				std::bind(
					&sge::camera::perspective_projection_from_viewport::viewport_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::camera::perspective_projection_from_viewport::~perspective_projection_from_viewport()
{
}

void
sge::camera::perspective_projection_from_viewport::viewport_callback(
	sge::renderer::target::viewport const &_viewport
)
{
	camera_.update_projection_matrix(
		sge::camera::projection_matrix(
			sge::renderer::projection::perspective_af(
				sge::renderer::projection::aspect(
					sge::renderer::target::aspect_from_viewport(
						_viewport
					)
				),
				fov_,
				near_,
				far_
			)
		)
	);
}
