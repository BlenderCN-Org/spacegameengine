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


#include <sge/opengl/create_onscreen_target.hpp>
#include <sge/opengl/onscreen_target.hpp>
#include <sge/opengl/backend/current_fwd.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/onscreen_unique_ptr.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::target::onscreen_unique_ptr
sge::opengl::create_onscreen_target(
	sge::opengl::context::object &_context,
	sge::opengl::backend::current &_current,
	awl::window::object &_window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::target::onscreen
		>(
			fcppt::make_unique_ptr<
				sge::opengl::onscreen_target
			>(
				_context,
				_current,
				_window
			)
		);
}
