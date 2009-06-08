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


#include <sge/renderer/filter/texture.hpp>

sge::renderer::filter::texture::texture(
	filter::min::type const min_,
	filter::mag::type const mag_,
	anisotropy_type const anisotropy_)
:
	min_(min_),
	mag_(mag_),
	anisotropy_(anisotropy_)
{}

sge::renderer::filter::min::type
sge::renderer::filter::texture::min() const
{
	return min_;
}

sge::renderer::filter::mag::type
sge::renderer::filter::texture::mag() const
{
	return mag_;
}

sge::renderer::filter::anisotropy_type
sge::renderer::filter::texture::anisotropy() const
{
	return anisotropy_;
}
