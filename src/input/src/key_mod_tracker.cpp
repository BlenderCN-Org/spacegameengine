/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../key_mod_tracker.hpp"
#include <boost/bind.hpp>

sge::key_mod_tracker::key_mod_tracker(const input_system_ptr is)
 : _state(false, false, false)
{
	is->register_callback(boost::bind(&key_mod_tracker::key_callback, this, _1));
}

void sge::key_mod_tracker::key_callback(const key_pair& p)
{
	const key_code c = p.first.code;
	if(is_shift(c))
		_state.shift = p.second;

	if(is_ctrl(c))
		_state.ctrl = p.second;

	if(is_alt(c))
		_state.alt = p.second;
}

const sge::mod_state& sge::key_mod_tracker::state() const
{
	return _state;
}
