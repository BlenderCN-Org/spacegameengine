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


#include <sge/d3d9/parameters/extract_size.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <awl/window/object.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::renderer::screen_size const
sge::d3d9::parameters::extract_size(
	sge::renderer::display_mode::optional_object const &_display_mode,
	awl::window::object &_window
)
{
	return
		fcppt::optional::maybe(
			_display_mode,
			[
				&_window
			]
			{
				return
					fcppt::math::dim::structure_cast<
						sge::renderer::screen_size,
						fcppt::cast::size_fun
					>(
						_window.size()
					);

			},
			[](
				sge::renderer::display_mode::object const &_mode
			)
			{
				return
					_mode.pixel_size().get();
			}
		);
}
