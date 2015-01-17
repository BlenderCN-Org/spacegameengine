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


#include <sge/input/cursor/choose_callback.hpp>
#include <sge/input/cursor/default_choose.hpp>
#include <sge/input/cursor/object_set.hpp>
#include <sge/input/cursor/optional_object_ref.hpp>


namespace
{

sge::input::cursor::optional_object_ref const
function(
	sge::input::cursor::object_set const &_objects
)
{
	return
		_objects.empty()
		?
			sge::input::cursor::optional_object_ref()
		:
			sge::input::cursor::optional_object_ref(
				**_objects.begin()
			)
		;
}

}

sge::input::cursor::choose_callback
sge::input::cursor::default_choose()
{
	return
		sge::input::cursor::choose_callback(
			function
		);
}
