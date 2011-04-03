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


#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/scoped_planar_lock.hpp>
#include <sge/renderer/device.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/dim.hpp>
#include <sge/image2d/view/format.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sge::renderer::texture::planar_ptr const
sge::renderer::texture::create_planar_from_view(
	renderer::device_ptr const _renderer,
	sge::image2d::view::const_object const &_view,
	texture::filter::object const &_filter,
	texture::address_mode2 const &_address_mode,
	renderer::resource_flags_field const &_resource_flags
)
{
	texture::planar_ptr const tex(
		_renderer->create_planar_texture(
			sge::renderer::texture::planar_parameters(
				sge::image2d::view::dim(
					_view
				),
				sge::image2d::view::format(
					_view
				),
				_filter,
				_address_mode,
				_resource_flags,
				renderer::texture::capabilities_field::null()
			)
		)
	);

	renderer::texture::scoped_planar_lock const lock(
		tex,
		renderer::lock_mode::writeonly
	);

	image2d::algorithm::copy_and_convert(
		_view,
		lock.value()
	);

	return tex;
}