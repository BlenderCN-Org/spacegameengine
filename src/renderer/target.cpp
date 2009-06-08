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


#include <sge/renderer/target.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/variant/object_impl.hpp>

sge::renderer::target::target()
{}

sge::image::view::const_object const
sge::renderer::target::lock() const
{
	return lock(
		rect()
	);
}

sge::renderer::target::rect_type const
sge::renderer::target::rect() const
{
	return rect_type(
		rect_type::point_type::null(),
		dim()
	);
}

sge::renderer::target::size_type
sge::renderer::target::size() const
{
	return dim().content();
}

sge::renderer::target::~target()
{}
