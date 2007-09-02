/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../../../exception.hpp"
#include "../conversion.hpp"

GLuint sge::ogl::convert_lock_flags(const lock_flag_t f)
{
	if(f & lock_flags::discard)
		return GL_WRITE_ONLY_ARB;
	return GL_READ_WRITE_ARB;
}

GLuint sge::ogl::convert_resource_flags(const resource_flag_t f)
{
	if(f & resource_flags::dynamic)
		return GL_DYNAMIC_DRAW_ARB;
	return GL_STATIC_DRAW_ARB;
}

template<> GLenum sge::ogl::convert_cast(const nonindexed_primitive_type::type& t)
{
	switch(t) {
	case nonindexed_primitive_type::point:
		return GL_POINTS;
	case nonindexed_primitive_type::line_strip:
		return GL_LINE_STRIP;
	case nonindexed_primitive_type::triangle_strip:
		return GL_TRIANGLE_STRIP;
	case nonindexed_primitive_type::triangle_fan:
		return GL_TRIANGLE_FAN;
	case nonindexed_primitive_type::line_loop:
		return GL_LINE_LOOP;
	default:
		throw exception("Invalid indexed_primitive_type!");
	}
}

template<> GLenum sge::ogl::convert_cast(const indexed_primitive_type::type& t)
{
	switch(t) {
	case indexed_primitive_type::line:
		return GL_LINES;
	case indexed_primitive_type::triangle:
		return GL_TRIANGLES;
	default:
		throw exception("Invalid nonindexed_primitive_type!");
	}
}

template<> GLenum sge::ogl::convert_cast(const bool_state::type& state)
{
	switch(state) {
	case bool_state::enable_alpha_blending:
		return GL_BLEND;
	case bool_state::enable_zbuffer:
		return GL_DEPTH_TEST;
	case bool_state::enable_stencil:
		return GL_STENCIL_TEST;
	case bool_state::enable_fog:
		return GL_FOG;
	case bool_state::enable_lighting:
		return GL_LIGHTING;
	case bool_state::enable_culling:
		return GL_CULL_FACE;
	default:
		throw exception("Invalid bool_state!");
	}
}

template<> GLenum sge::ogl::convert_cast(const min_filter::type& arg)
{
	switch(arg) {
	case min_filter::point:
		return GL_NEAREST;
	case min_filter::linear:
		return GL_LINEAR;
	case min_filter::mipmap:
		return GL_LINEAR_MIPMAP_NEAREST;
	case min_filter::trilinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	default:
		throw exception("Invalid min_filter!");
	}
}

template<> GLenum sge::ogl::convert_cast(const mag_filter::type& arg)
{
	switch(arg) {
	case mag_filter::point:
		return GL_NEAREST;
	case mag_filter::linear:
		return GL_LINEAR;
	default:
		throw exception("Invalid mag_filter!");
	}
}
template<> GLenum sge::ogl::convert_cast(const cube_side::type& s)
{
	switch(s) {
	case cube_side::left:
		return GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB;
	case cube_side::right:
		return GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB;
	case cube_side::front:
		return GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB;
	case cube_side::back:
		return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB;
	case cube_side::top:
		return GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB;
	case cube_side::bottom:
		return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB;
	default:
		throw exception("Invalid cube_side!");
	}
}

template<> GLenum sge::ogl::convert_cast(const cull_mode::type& m)
{
	switch(m) {
	case cull_mode::back:
		return GL_BACK;
	case cull_mode::front:
		return GL_FRONT;
	default:
		throw exception("Invalid cull_mode!");
	}
}

template<> GLenum sge::ogl::convert_cast(const compare_func::type& f)
{
	switch(f) {
	case compare_func::never:
		return GL_NEVER;
	case compare_func::less:
		return GL_LESS;
	case compare_func::equal:
		return GL_EQUAL;
	case compare_func::less_equal:
		return GL_LEQUAL;
	case compare_func::greater:
		return GL_GREATER;
	case compare_func::not_equal:
		return GL_NOTEQUAL;
	case compare_func::greater_equal:
		return GL_GEQUAL;
	case compare_func::always:
		return GL_ALWAYS;
	default:
		throw exception("Invalid compare_func!");
	}
}

template<> GLenum sge::ogl::convert_cast(const fog_mode::type& m)
{
	switch(m) {
	case fog_mode::linear:
		return GL_LINEAR;
	case fog_mode::exp:
		return GL_EXP;
	case fog_mode::exp2:
		return GL_EXP2;
	default:
		throw exception("Invalid fog_mode!");
	}
}

template<> GLenum sge::ogl::convert_cast(const source_blend_func::type& f)
{
	switch(f) {
	case source_blend_func::zero:
		return GL_ZERO;
	case source_blend_func::one:
		return GL_ONE;
	case source_blend_func::dest_color:
		return GL_DST_COLOR;
	case source_blend_func::inv_dest_color:
		return GL_ONE_MINUS_DST_COLOR;
	case source_blend_func::src_alpha:
		return GL_SRC_ALPHA;
	case source_blend_func::inv_src_alpha:
		return GL_ONE_MINUS_SRC_ALPHA;
	case source_blend_func::dest_alpha:
		return GL_DST_ALPHA;
	case source_blend_func::inv_dest_alpha:
		return GL_ONE_MINUS_DST_ALPHA;
	case source_blend_func::src_alpha_sat:
		return GL_SRC_ALPHA_SATURATE;
	default:
		throw exception("Invalid source_blend_func!");
	}
}

template<> GLenum sge::ogl::convert_cast(const dest_blend_func::type& f)
{
	switch(f) {
	case dest_blend_func::zero:
		return GL_ZERO;
	case dest_blend_func::one:
		return GL_ONE;
	case dest_blend_func::src_color:
		return GL_SRC_COLOR;
	case dest_blend_func::inv_src_color:
		return GL_ONE_MINUS_SRC_COLOR;
	case dest_blend_func::src_alpha:
		return GL_SRC_ALPHA;
	case dest_blend_func::inv_src_alpha:
		return GL_ONE_MINUS_SRC_ALPHA;
	case dest_blend_func::dest_alpha:
		return GL_DST_ALPHA;
	case dest_blend_func::inv_dest_alpha:
		return GL_ONE_MINUS_DST_ALPHA;
	default:
		throw exception("Invalid dest_blend_func!");
	}
}

template<> GLenum sge::ogl::convert_cast(const texture_stage_op::type& op)
{
	switch(op) {
	case texture_stage_op::color:
		return GL_COMBINE_RGB_ARB;
	case texture_stage_op::alpha:
		return GL_COMBINE_ALPHA_ARB;
	default:
		throw exception("Invalid texture_stage_op!");
	}
}

template<> GLenum sge::ogl::convert_cast(const texture_stage_op_value::type& value)
{
	switch(value) {
	case texture_stage_op_value::arg0:
		return GL_REPLACE;
	case texture_stage_op_value::modulate:
	case texture_stage_op_value::modulate2x:
	case texture_stage_op_value::modulate4x:
		return GL_MODULATE;
	case texture_stage_op_value::add:
	case texture_stage_op_value::add2x:
	case texture_stage_op_value::add4x:
		return GL_ADD;
	case texture_stage_op_value::substract:
		return GL_SUBTRACT_ARB;
	case texture_stage_op_value::add_signed:
	case texture_stage_op_value::add_signed2x:
		return GL_ADD_SIGNED_ARB;
	case texture_stage_op_value::interpolate:
		return GL_INTERPOLATE_ARB;
	default:
		throw exception("Invalid texture_stage_op_value!");
	}
}

template<> GLenum sge::ogl::convert_cast(const texture_stage_arg::type& arg)
{
	switch(arg) {
	case texture_stage_arg::rgb0:
		return GL_SOURCE0_RGB_ARB;
	case texture_stage_arg::rgb1:
		return GL_SOURCE1_RGB_ARB;
	case texture_stage_arg::rgb2:
		return GL_SOURCE2_RGB_ARB;
	case texture_stage_arg::alpha0:
		return GL_SOURCE0_ALPHA_ARB;
	case texture_stage_arg::alpha1:
		return GL_SOURCE1_ALPHA_ARB;
	case texture_stage_arg::alpha2:
		return GL_SOURCE2_ALPHA_ARB;
	default:
		throw exception("Invalid texture_stage_arg!");
	}
}

template<> GLenum sge::ogl::convert_cast(const texture_stage_arg_value::type& value)
{
	switch(value) {
	case texture_stage_arg_value::current:
		return GL_PRIMARY_COLOR_ARB;
	case texture_stage_arg_value::texture:
		return GL_TEXTURE;
	case texture_stage_arg_value::constant:
		return GL_CONSTANT_ARB;
	default:
		throw exception("Invalid texture_stage_arg_value!");
	}
}

GLenum sge::ogl::convert_fog_float_state(const float_state::type& s)
{
	switch(s) {
	case float_state::fog_start:
		return GL_FOG_START;
	case float_state::fog_end:
		return GL_FOG_END;
	case float_state::fog_density:
		return GL_FOG_DENSITY;
	default:
		throw exception("Invalid fog float_state!");
	}
}
