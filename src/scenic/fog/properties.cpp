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


#include <sge/scenic/fog/properties.hpp>

sge::scenic::fog::properties::properties(
	sge::scenic::fog::start const &_start,
	sge::scenic::fog::end const &_end,
	sge::scenic::fog::color const &_color)
:
	start_(
		_start),
	end_(
		_end),
	color_(
		_color)
{
}

sge::scenic::fog::start const &
sge::scenic::fog::properties::start() const
{
	return
		start_;
}

sge::scenic::fog::end const &
sge::scenic::fog::properties::end() const
{
	return
		end_;
}

sge::scenic::fog::color const &
sge::scenic::fog::properties::color() const
{
	return
		color_;
}
