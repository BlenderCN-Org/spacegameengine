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


#include "../clear.hpp"

sge::d3d9::state::clear::clear()
:
	color_(0),
	depth_(0.f),
	stencil_(0),
	flags_(0)
{
}

void
sge::d3d9::state::clear::color(
	D3DCOLOR const _color
)
{
	color_ = _color;
}

void
sge::d3d9::state::clear::depth(
	float const _depth
)
{
	depth_ = _depth;
}

void
sge::d3d9::state::clear::stencil(
	DWORD const _stencil
)
{
	stencil_ = _stencil;
}

void
sge::d3d9::state::clear::flag(
	DWORD const _flag,
	bool const _value
)
{
	if(
		_value
	)
		flags_ |= _flag;
	else
		flags_ &= ~_flag;
}

D3DCOLOR
sge::d3d9::state::clear::color() const
{
	return color_;
}

float
sge::d3d9::state::clear::depth() const
{
	return depth_;
}

DWORD
sge::d3d9::state::clear::stencil() const
{
	return stencil_;
}

DWORD
sge::d3d9::state::clear::flags() const
{
	return flags_;
}
