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


#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/depth_stencil_to_format.hpp>
#include <sge/opengl/convert/depth_stencil_to_format_type.hpp>
#include <sge/opengl/convert/depth_stencil_to_internal_format.hpp>
#include <sge/opengl/texture/depth_stencil.hpp>
#include <sge/opengl/texture/depth_stencil_surface.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/convert/make_type.hpp>
#include <sge/opengl/texture/funcs/set_2d.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/depth_stencil_parameters.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>


// FIXME: this should inherit from basic_texture as well!
sge::opengl::texture::depth_stencil::depth_stencil(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::texture::depth_stencil_parameters const &_params
)
:
	sge::renderer::texture::depth_stencil(),
	sge::opengl::texture::base(
		sge::opengl::texture::convert::make_type(
			GL_TEXTURE_2D
		)
	),
	system_context_(
		_system_context
	),
	size_(
		_params.size()
	),
	format_(
		_params.format()
	)
{
	sge::opengl::texture::scoped_work_binding const binding(
		_system_context,
		this->type(),
		this->id()
	);

	sge::opengl::texture::funcs::set_2d(
		binding,
		_system_context,
		this->type(),
		sge::opengl::convert::depth_stencil_to_format(
			format_
		),
		sge::opengl::convert::depth_stencil_to_format_type(
			format_
		),
		sge::opengl::convert::depth_stencil_to_internal_format(
			format_
		),
		sge::renderer::texture::mipmap::level(
			0u
		),
		this->size(),
		fcppt::null_ptr()
	);
}

sge::opengl::texture::depth_stencil::~depth_stencil()
{
}

sge::opengl::texture::depth_stencil::dim const
sge::opengl::texture::depth_stencil::size() const
{
	return size_;
}

sge::renderer::depth_stencil_surface_unique_ptr
sge::opengl::texture::depth_stencil::surface() const
{
	opengl::texture::scoped_work_binding const binding(
		system_context_,
		this->type(),
		this->id()
	);

	return
		sge::renderer::depth_stencil_surface_unique_ptr(
			fcppt::make_unique_ptr<
				opengl::texture::depth_stencil_surface
			>(
				fcppt::cref(
					binding
				),
				this->type(),
				this->id(),
				format_
			)
		);
}

sge::renderer::resource_flags_field const
sge::opengl::texture::depth_stencil::resource_flags() const
{
	return renderer::resource_flags::none;
}

sge::renderer::texture::capabilities_field const
sge::opengl::texture::depth_stencil::capabilities() const
{
	return
		renderer::texture::capabilities_field(
			renderer::texture::capabilities::render_target
		);
}

sge::renderer::texture::mipmap::object const
sge::opengl::texture::depth_stencil::mipmap() const
{
	return renderer::texture::mipmap::off();
}
