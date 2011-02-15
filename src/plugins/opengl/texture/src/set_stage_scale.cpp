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


#include "../set_stage_scale.hpp"
#include "../funcs/envf.hpp"
#include "../../common.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

namespace
{

GLenum
stage_value_scale(
	sge::renderer::sampler_stage_op_value::type const _value
)
{
	switch(
		_value
	)
	{
	case sge::renderer::sampler_stage_op_value::arg0:
	case sge::renderer::sampler_stage_op_value::modulate:
	case sge::renderer::sampler_stage_op_value::add:
	case sge::renderer::sampler_stage_op_value::substract:
	case sge::renderer::sampler_stage_op_value::add_signed:
	case sge::renderer::sampler_stage_op_value::interpolate:
		return 1;
	case sge::renderer::sampler_stage_op_value::modulate2x:
	case sge::renderer::sampler_stage_op_value::add2x:
	case sge::renderer::sampler_stage_op_value::add_signed2x:
		return 2;
	case sge::renderer::sampler_stage_op_value::modulate4x:
	case sge::renderer::sampler_stage_op_value::add4x:
		return 4;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid sampler_stage_op_value!")
	);
}

}

void
sge::opengl::texture::set_stage_scale(
	renderer::sampler_stage_op_value::type const _value
)
{
	GLenum const scale(
		::stage_value_scale(
			_value
		)
	);

	opengl::texture::funcs::envf(
		GL_RGB_SCALE,
		scale
	);

	opengl::texture::funcs::envf(
		GL_ALPHA_SCALE,
		scale
	);
}
