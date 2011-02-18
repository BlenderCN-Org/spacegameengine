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


#include "../bind_context.hpp"
#include "../base.hpp"
#include "../const_base_ptr.hpp"
#include "../optional_type.hpp"
#include "../funcs/bind.hpp"
#include "../funcs/set_active_level.hpp"
#include "../../context/make_id.hpp"
#include "../../disable.hpp"
#include "../../enable.hpp"
#include <fcppt/container/index_map_impl.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/weak_ptr_impl.hpp>

sge::opengl::texture::bind_context::bind_context()
:
	render_textures_(),
	temp_textures_(),
	last_types_()
{
}

sge::opengl::texture::bind_context::~bind_context()
{
}

void
sge::opengl::texture::bind_context::bind_for_rendering(
	opengl::context::object &_context,
	opengl::texture::const_base_ptr const _texture,
	renderer::stage_type const _stage
)
{
	render_textures_[
		_stage.get()
	] = _texture;

	// Check that there is no temp binding active
	// because we would override it otherwise!
	FCPPT_ASSERT(
		!temp_textures_[
			_stage.get()
		].lock()
	);

	texture::funcs::set_active_level(
		_context,
		_stage
	);

	texture::funcs::bind(
		_texture->type(),
		_texture->id()
	);

	texture::optional_type const last_type(
		last_types_[
			_stage.get()
		]
	);

	if(
		last_type
		!=
		texture::optional_type(
			_texture->type()
		)
	)
	{
		if(
			last_type
		)
			opengl::disable(
				last_type->get()
			);

		opengl::enable(
			_texture->type().get()
		);

		last_types_[
			_stage.get()
		] = _texture->type();
	}
}

void
sge::opengl::texture::bind_context::unbind_for_rendering(
	opengl::context::object &_context,
	renderer::stage_type const _stage
)
{
	FCPPT_ASSERT(
		!temp_textures_[
			_stage.get()
		].lock()
	);

	texture::funcs::set_active_level(
		_context,
		_stage
	);

	texture::optional_type const last_type(
		last_types_[
			_stage.get()
		]
	);

	if(
		last_type
	)
		texture::funcs::bind(
			*last_type,
			texture::id(
				0u
			)
		);

	render_textures_[
		_stage.get()
	].reset();

	last_types_[
		_stage.get()
	] = texture::optional_type();
}

void
sge::opengl::texture::bind_context::bind_for_work(
	opengl::context::object &_context,
	texture::type const _type,
	texture::id const _id,
	renderer::stage_type const _stage
)
{
	temp_textures_[
		_stage.get()
	] =
		render_textures_[
			_stage.get()
		];
	
	texture::funcs::set_active_level(
		_context,
		_stage
	);

	texture::funcs::bind(
		_type,
		_id
	);
}

void
sge::opengl::texture::bind_context::unbind_for_work(
	opengl::context::object &_context,
	renderer::stage_type const _stage
)
{
	texture::const_base_ptr const prev_texture(
		temp_textures_[
			_stage.get()
		].lock()
	);

	render_textures_[
		_stage.get()
	] =
		prev_texture;

	temp_textures_[
		_stage.get()
	].reset();
	
	if(
		prev_texture
	)
		this->bind_for_rendering(
			_context,
			prev_texture,
			_stage
		);
}

sge::opengl::context::id const
sge::opengl::texture::bind_context::static_id(
	sge::opengl::context::make_id()
);
