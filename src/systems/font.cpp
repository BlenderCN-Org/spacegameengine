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


#include <sge/plugin/name.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/optional_name.hpp>


sge::systems::font::font()
:
	name_()
{
}

sge::systems::font &
sge::systems::font::name(
	sge::plugin::name const &_name
)
{
	name_ = _name;

	return *this;
}

sge::systems::optional_name const &
sge::systems::font::name() const
{
	return name_;
}
