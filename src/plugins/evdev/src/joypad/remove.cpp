/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/evdev/joypad/map.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/remove.hpp>
#include <sge/input/joypad/remove_event.hpp>
#include <sge/input/joypad/remove_signal.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


void
sge::evdev::joypad::remove(
	sge::evdev::joypad::map &_map,
	sge::input::joypad::remove_signal &_signal,
	boost::filesystem::path const &_path
)
{
	sge::evdev::joypad::map::iterator const it(
		_map.find(
			_path
		)
	);

	if(
		it == _map.end()
	)
		return;

	_signal(
		sge::input::joypad::remove_event(
			*it->second
		)
	);

	_map.erase(
		it
	);
}
