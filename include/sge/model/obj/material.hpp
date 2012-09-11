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


#ifndef SGE_MODEL_OBJ_MATERIAL_HPP_INCLUDED
#define SGE_MODEL_OBJ_MATERIAL_HPP_INCLUDED

#include <sge/model/obj/identifier.hpp>
#include <sge/model/obj/symbol.hpp>
#include <sge/model/obj/diffuse_texture_path.hpp>
#include <sge/model/obj/specular_texture_path.hpp>
#include <sge/renderer/material.hpp>


namespace sge
{
namespace model
{
namespace obj
{
class material
{
public:
	SGE_MODEL_OBJ_SYMBOL
	material(
		sge::model::obj::identifier const &,
		sge::renderer::material const &,
		sge::model::obj::diffuse_texture_path const &,
		sge::model::obj::specular_texture_path const &);

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::identifier const &
	identifier() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::renderer::material const &
	renderer_material() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::diffuse_texture_path const &
	diffuse_texture() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::specular_texture_path const &
	specular_texture() const;
private:
	sge::model::obj::identifier identifier_;
	sge::renderer::material renderer_material_;
	sge::model::obj::diffuse_texture_path diffuse_texture_;
	sge::model::obj::specular_texture_path specular_texture_;
};
}
}
}

#endif
