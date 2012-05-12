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


#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/opengl/cg/texture/load.hpp>
#include <sge/opengl/cg/texture/loaded_object.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>


sge::renderer::cg::loaded_texture_unique_ptr
sge::opengl::cg::texture::load(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::context::device::object &_device_context,
	sge::cg::parameter::object const &_parameter,
	sge::renderer::texture::base &_texture
)
{
	return
		sge::renderer::cg::loaded_texture_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::cg::texture::loaded_object
			>(
				fcppt::ref(
					_system_context
				),
				fcppt::ref(
					_device_context
				),
				fcppt::cref(
					_parameter
				),
				fcppt::ref(
					_texture
				)
			)
		);
}
