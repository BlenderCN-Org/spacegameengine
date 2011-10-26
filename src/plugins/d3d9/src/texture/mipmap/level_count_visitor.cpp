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


#include <sge/d3d9/texture/mipmap/level_count_visitor.hpp>
#include <sge/renderer/texture/mipmap/levels_rep.hpp>

sge::d3d9::texture::mipmap::level_count_visitor::result_type
sge::d3d9::texture::mipmap::level_count_visitor::operator()(
	renderer::texture::mipmap::all_levels_rep const &
) const
{
	return 0u;
}

sge::d3d9::texture::mipmap::level_count_visitor::result_type
sge::d3d9::texture::mipmap::level_count_visitor::operator()(
	renderer::texture::mipmap::levels_rep const &_rep
) const
{
	return _rep.value().get();
}

sge::d3d9::texture::mipmap::level_count_visitor::result_type
sge::d3d9::texture::mipmap::level_count_visitor::operator()(
	renderer::texture::mipmap::off_rep const &
) const
{
	return 1u;
}
