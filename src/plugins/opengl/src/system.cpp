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


#include <sge/opengl/create_device_caps.hpp>
#include <sge/opengl/create_visual.hpp>
#include <sge/opengl/device.hpp>
#include <sge/opengl/system.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/device_unique_ptr.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/caps/device_count.hpp>
#include <sge/renderer/caps/system.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assert/pre.hpp>


sge::opengl::system::system()
:
	system_context_(),
	caps_(
		sge::opengl::create_device_caps(
			system_context_
		)
	)
{
}

sge::opengl::system::~system()
{
}

sge::renderer::device_unique_ptr
sge::opengl::system::create_renderer(
	sge::renderer::parameters const &_parameters,
	sge::renderer::adapter const _adapter,
	awl::window::object &_window
)
{
	FCPPT_ASSERT_PRE(
		_adapter.get()
		<
		this->device_count().get()
	);

	return
		sge::renderer::device_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::device
			>(
				fcppt::cref(
					_parameters
				),
				fcppt::ref(
					_window
				),
				fcppt::ref(
					system_context_
				),
				fcppt::cref(
					*caps_
				)
			)
		);
}

awl::visual::object_unique_ptr
sge::opengl::system::create_visual(
	awl::system::object &_awl_system,
	sge::renderer::parameters const &_parameters
)
{
	return
		sge::opengl::create_visual(
			_awl_system,
			_parameters
		);
}

sge::renderer::caps::system_field const
sge::opengl::system::caps() const
{
	return
		sge::renderer::caps::system_field(
			sge::renderer::caps::system::opengl
		);
}

sge::renderer::caps::device_count const
sge::opengl::system::device_count() const
{
	return
		sge::renderer::caps::device_count(
			1u
		);
}

sge::renderer::caps::device const &
sge::opengl::system::device_caps(
	sge::renderer::adapter const _adapter
) const
{
	FCPPT_ASSERT_PRE(
		_adapter.get()
		<
		this->device_count().get()
	);

	return
		*caps_;
}
