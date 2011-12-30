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


#include <sge/renderer/device.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/texture/atlasing/create.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


sge::renderer::texture::planar_ptr const
sge::texture::atlasing::create(
	renderer::device &_rend,
	image::color::format::type const _format,
	renderer::texture::mipmap::object const &_mipmap,
	renderer::dim2 const &_dim
)
{
	return
		_rend.create_planar_texture(
			renderer::texture::planar_parameters(
				_dim,
				_format,
				_mipmap,
				renderer::resource_flags::none,
				renderer::texture::capabilities_field::null()
			)
		);
}
