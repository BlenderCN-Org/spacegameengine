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


#include <sge/renderer/device/index.hpp>
#include <sge/renderer/device/parameters.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <awl/window/object_fwd.hpp>
#include <awl/window/event/processor_fwd.hpp>


sge::renderer::device::parameters::parameters(
	sge::renderer::device::index const _index,
	sge::renderer::display_mode::parameters const &_display_mode,
	awl::window::object &_window,
	awl::window::event::processor &_window_processor
)
:
	index_(
		_index
	),
	display_mode_(
		_display_mode
	),
	window_(
		_window
	),
	window_processor_(
		_window_processor
	)
{
}

sge::renderer::device::index
sge::renderer::device::parameters::index() const
{
	return
		index_;
}

sge::renderer::display_mode::parameters const &
sge::renderer::device::parameters::display_mode() const
{
	return
		display_mode_;
}

awl::window::object &
sge::renderer::device::parameters::window() const
{
	return
		window_;
}

awl::window::event::processor &
sge::renderer::device::parameters::window_processor() const
{
	return
		window_processor_;
}
