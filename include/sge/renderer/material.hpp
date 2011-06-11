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


#ifndef SGE_RENDERER_MATERIAL_HPP_INCLUDED
#define SGE_RENDERER_MATERIAL_HPP_INCLUDED

#include <sge/renderer/material_fwd.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/image/color/any/object.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace sge
{
namespace renderer
{

class material
{
public:
	SGE_RENDERER_SYMBOL material(
		image::color::any::object const &diffuse,
		image::color::any::object const &ambient,
		image::color::any::object const &specular,
		image::color::any::object const &emissive,
		scalar const &power
	);

	SGE_RENDERER_SYMBOL image::color::any::object const &
	diffuse() const;

	SGE_RENDERER_SYMBOL image::color::any::object const &
	ambient() const;

	SGE_RENDERER_SYMBOL image::color::any::object const &
	specular() const;

	SGE_RENDERER_SYMBOL image::color::any::object const &
	emissive() const;

	SGE_RENDERER_SYMBOL scalar const &
	power() const;
private:
	image::color::any::object
		diffuse_,
		ambient_,
		specular_,
		emissive_;
	
	scalar power_;
};

}
}

#endif
