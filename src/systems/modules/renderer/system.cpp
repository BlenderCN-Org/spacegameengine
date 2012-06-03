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


#include <sge/plugin/manager_fwd.hpp>
#include <sge/plugin/object.hpp>
#include <sge/renderer/plugin.hpp>
#include <sge/renderer/system.hpp>
#include <sge/src/systems/add_plugin.hpp>
#include <sge/src/systems/plugin_cache_fwd.hpp>
#include <sge/src/systems/modules/renderer/find_plugin.hpp>
#include <sge/src/systems/modules/renderer/system.hpp>
#include <sge/systems/renderer.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>


sge::systems::modules::renderer::system::system(
	sge::systems::plugin_cache &_plugin_cache,
	sge::plugin::manager &_plugin_manager,
	sge::systems::renderer const &_parameters
)
:
	plugin_(
		sge::systems::add_plugin(
			_plugin_cache,
			sge::systems::modules::renderer::find_plugin(
				_plugin_manager,
				_parameters.caps()
			)
		)
	),
	renderer_parameters_(
		_parameters.parameters()
	),
	renderer_system_(
		plugin_->get()()
	)
{
}

sge::systems::modules::renderer::system::~system()
{
}

awl::visual::object_unique_ptr
sge::systems::modules::renderer::system::create_visual(
	awl::system::object &_awl_system
)
{
	return
		renderer_system_->create_visual(
			_awl_system,
			renderer_parameters_
		);
}

sge::renderer::system &
sge::systems::modules::renderer::system::get() const
{
	return *renderer_system_;
}
