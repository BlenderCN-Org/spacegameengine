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


#include <sge/opengl/fbo/attach_texture_2d.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/context_fwd.hpp>
#include <sge/opengl/fbo/texture_binding.hpp>
#include <sge/opengl/texture/surface_base.hpp>
#include <sge/opengl/texture/surface_base_ptr.hpp>


sge::opengl::fbo::texture_binding::texture_binding(
	sge::opengl::fbo::context const &_context,
	sge::opengl::texture::surface_base_ptr const _surface,
	sge::opengl::fbo::attachment_type const _attachment
)
:
	context_(
		_context
	),
	surface_(
		_surface
	),
	attachment_(
		_attachment
	)
{
	sge::opengl::fbo::attach_texture_2d(
		_context,
		_attachment,
		_surface->type(),
		_surface->id(),
		_surface->level()
	);
}

sge::opengl::fbo::texture_binding::~texture_binding()
{
	sge::opengl::fbo::attach_texture_2d(
		context_,
		attachment_,
		surface_->type(),
		sge::opengl::texture::id(
			0u
		),
		surface_->level()
	);
}
