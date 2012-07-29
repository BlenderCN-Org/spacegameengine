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


#include <sge/renderer/texture/mipmap/all_levels_rep.hpp>
#include <sge/renderer/texture/mipmap/auto_generate.hpp>


sge::renderer::texture::mipmap::all_levels_rep::all_levels_rep(
	sge::renderer::texture::mipmap::auto_generate::type const _auto_generate
)
:
	auto_generate_(
		_auto_generate
	)
{
}

sge::renderer::texture::mipmap::auto_generate::type
sge::renderer::texture::mipmap::all_levels_rep::auto_generate() const
{
	return auto_generate_;
}
