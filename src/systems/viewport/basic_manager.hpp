/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_VIEWPORT_BASIC_MANAGER_HPP_INCLUDED
#define SGE_SYSTEMS_VIEWPORT_BASIC_MANAGER_HPP_INCLUDED

#include "resize_function.hpp"
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/target_base_ptr.hpp>
#include <sge/systems/viewport/manage_callback.hpp>
#include <sge/systems/viewport/manage_function.hpp>
#include <sge/systems/viewport/manager.hpp>
#include <awl/window/event/resize_fwd.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace systems
{
namespace viewport
{

class basic_manager
:
	public sge::systems::viewport::manager
{
	FCPPT_NONCOPYABLE(
		basic_manager
	);
public:
	explicit basic_manager(
		sge::renderer::device_ptr,
		systems::viewport::resize_function const &
	);
	
	~basic_manager();

	fcppt::signal::auto_connection
	manage_callback(
		systems::viewport::manage_callback const &
	);
private:
	void
	on_resize(
		awl::window::event::resize const &
	);

	sge::renderer::device_ptr const device_;

	sge::renderer::target_base_ptr const target_;

	systems::viewport::resize_function const resize_function_;

	fcppt::signal::scoped_connection const resize_connection_;

	typedef fcppt::signal::object<
		systems::viewport::manage_function
	> manage_signal;

	manage_signal manage_signal_;
};

}
}
}

#endif
