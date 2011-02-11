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


#include "../object.hpp"
#include "../basic_impl.hpp"
#include "../scoped_work_bind.hpp"
#include "../surface.hpp"
#include "../funcs/get_parameter_int.hpp"
#include "../funcs/set.hpp"
#include "../funcs/set_rect.hpp"
#include "../../common.hpp"
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/texture.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>

template class
sge::opengl::texture::basic<
	sge::renderer::texture
>;

sge::opengl::texture::object::object(
	context::object &_context,
	dim_type const &_dim,
	image::color::format::type const _format,
	renderer::filter::texture const &_filter,
	renderer::resource_flags_field const &_flags,
	optional_type const &_type
)
:
	object_base(
		_context,
		_filter,
		_flags,
		_type
		?
			*_type
		:
			opengl::texture::type(
				GL_TEXTURE_2D
			),
		_format,
		_dim
	)
{
	opengl::texture::scoped_work_bind const binding(
		_context,
		*this,
		renderer::stage_type(0u)
	);

	opengl::texture::funcs::set(
		binding,
		_context,
		this->type(),
		this->format(),
		this->format_type(),
		this->internal_format(),
		this->filter(),
		this->dim(),
		0
	);
}

sge::opengl::texture::object::~object()
{
}

void
sge::opengl::texture::object::set_area(
	opengl::texture::scoped_work_bind const &_binding,
	lock_area const &_area,
	pointer const _dest
) const
{
	opengl::texture::funcs::set_rect(
		_binding,
		this->context(),
		this->type(),
		this->format(),
		this->format_type(),
		this->dim(),
		_area,
		_dest
	);
}

sge::renderer::color_surface_ptr const
sge::opengl::texture::object::surface(
	renderer::stage_type const _stage
)
{
	opengl::texture::scoped_work_bind const binding(
		this->context(),
		*this,
		renderer::stage_type(0u)
	);

	return
		fcppt::make_shared_ptr<
			opengl::texture::surface
		>(
			binding,
			this->type(),
			this->id(),
			_stage
		);
}

sge::renderer::stage_type
sge::opengl::texture::object::stages() const
{
	opengl::texture::scoped_work_bind const binding(
		this->context(),
		*this,
		renderer::stage_type(0u)
	);

	return
		renderer::stage_type(
			static_cast<
				renderer::stage_type::value_type
			>(
				funcs::get_parameter_int(
					binding,
					this->type(),
					GL_TEXTURE_BASE_LEVEL
				)
			)
		);
}
