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


#include <sge/renderer/display_mode/comparison.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/math/dim/comparison.hpp>


bool
sge::renderer::display_mode::operator==(
	sge::renderer::display_mode::object const &_left,
	sge::renderer::display_mode::object const &_right
)
{
	return
		_left.pixel_size() == _right.pixel_size()
		&& _left.dimensions() == _right.dimensions()
		&& _left.refresh_rate() == _right.refresh_rate();
}

bool
sge::renderer::display_mode::operator!=(
	sge::renderer::display_mode::object const &_left,
	sge::renderer::display_mode::object const &_right
)
{
	return
		!(_left == _right);
}
