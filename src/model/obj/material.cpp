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


#include <sge/model/obj/material.hpp>

sge::model::obj::material::material(
	sge::model::obj::identifier const &_identifier,
	sge::renderer::material const &_renderer_material,
	sge::model::obj::diffuse_texture_path const &_diffuse_texture,
	sge::model::obj::specular_texture_path const &_specular_texture)
:
	identifier_(
		_identifier),
	renderer_material_(
		_renderer_material),
	diffuse_texture_(
		_diffuse_texture),
	specular_texture_(
		_specular_texture)
{
}

sge::model::obj::identifier const &
sge::model::obj::material::identifier() const
{
	return
		identifier_;
}

sge::renderer::state::ffp::lighting::material::parameters const &
sge::model::obj::material::renderer_material() const
{
	return
		renderer_material_;
}

sge::model::obj::diffuse_texture_path const &
sge::model::obj::material::diffuse_texture() const
{
	return
		diffuse_texture_;
}

sge::model::obj::specular_texture_path const &
sge::model::obj::material::specular_texture() const
{
	return
		specular_texture_;
}
