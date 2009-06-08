/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/gui/layouts/horizontal.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>

sge::gui::layouts::horizontal::horizontal()
	: row()
{
}

sge::gui::dim::reference sge::gui::layouts::horizontal::master(
	dim &d) const
{
	return d.w();
}

sge::gui::dim::const_reference sge::gui::layouts::horizontal::master(
	dim const &d) const
{
	return d.w();
}

sge::gui::point::reference sge::gui::layouts::horizontal::master(
	point &d) const
{
	return d.x();
}

sge::gui::point::const_reference sge::gui::layouts::horizontal::master(
	point const &d) const
{
	return d.x();
}
