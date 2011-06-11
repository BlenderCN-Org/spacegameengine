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


#ifndef SGE_RENDERER_LIGHT_HPP_INCLUDED
#define SGE_RENDERER_LIGHT_HPP_INCLUDED

#include <sge/renderer/light_fwd.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

namespace sge
{
namespace renderer
{

class light
{
public:
	typedef vector3 position_type;
	typedef vector3 direction_type;
	typedef scalar attenuation_type;

	SGE_RENDERER_SYMBOL light(
		image::color::any::object const &ambient,
		image::color::any::object const &diffuse,
		image::color::any::object const &specular,
		position_type const &pos,
		direction_type const &dir,
		attenuation_type const &const_attenuation,
		attenuation_type const &linear_attenuation,
		attenuation_type const &quadratic_attenuation,
		scalar const &distribution_exponent,
		scalar const &cutoff_angle
	);

	SGE_RENDERER_SYMBOL image::color::any::object const &
	ambient() const;

	SGE_RENDERER_SYMBOL image::color::any::object const &
	diffuse() const;

	SGE_RENDERER_SYMBOL image::color::any::object const &
	specular() const;

	SGE_RENDERER_SYMBOL position_type const &
	position() const;

	SGE_RENDERER_SYMBOL direction_type const &
	direction() const;

	SGE_RENDERER_SYMBOL attenuation_type const &
	const_attenuation() const;

	SGE_RENDERER_SYMBOL attenuation_type const &
	linear_attenuation() const;

	SGE_RENDERER_SYMBOL attenuation_type const &
	quadratic_attenuation() const;

	SGE_RENDERER_SYMBOL scalar const &
	distribution_exponent() const;

	SGE_RENDERER_SYMBOL scalar const &
	cutoff_angle() const;
private:
	image::color::any::object
		ambient_,
		diffuse_,
		specular_;
	position_type position_;
	direction_type  direction_;
	attenuation_type
		const_attenuation_,
		linear_attenuation_,
		quadratic_attenuation_;
	scalar
		distribution_exponent_,
		cutoff_angle_;
};

}
}

#endif
