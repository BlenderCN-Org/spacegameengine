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


#include <sge/src/systems/modules/renderer/optional_system_ref.hpp>
#include <sge/src/systems/modules/window/base.hpp>
#include <sge/src/systems/modules/window/make_base.hpp>
#include <sge/src/systems/modules/window/object.hpp>
#include <sge/src/systems/modules/window/quit.hpp>
#include <sge/systems/window.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


sge::systems::modules::window::object::object(
	sge::systems::window const &_parameters,
	sge::systems::modules::renderer::optional_system_ref const &_renderer_system
)
:
	base_(
		sge::systems::modules::window::make_base(
			_parameters,
			_renderer_system
		)
	),
	show_on_post_(
		_parameters.show()
	),
	quit_(
		_parameters.quit()
		?
			fcppt::make_unique_ptr<
				sge::systems::modules::window::quit
			>(
				base_->system(),
				base_->window()
			)
		:
			std::unique_ptr<
				sge::systems::modules::window::quit
			>()
	)
{
}

sge::systems::modules::window::object::~object()
{
}

sge::window::system &
sge::systems::modules::window::object::system() const
{
	return base_->system();
}

sge::window::object &
sge::systems::modules::window::object::window() const
{
	return base_->window();
}

void
sge::systems::modules::window::object::post_init()
{
	if(
		show_on_post_
	)
		this->window().show();
}
