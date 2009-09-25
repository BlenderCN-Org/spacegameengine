/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <boost/foreach.hpp>
#include "../device.hpp"
#include "../pbo.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../vertex_buffer.hpp"
#include "../texture.hpp"
#include "../cube_texture.hpp"
#include "../volume_texture.hpp"
#include "../convert_clear_bit.hpp"
#include "../default_target.hpp"
#include "../light.hpp"
#include "../enable.hpp"
#include "../multi_texture.hpp"
#include "../texture_stage.hpp"
#include "../basic_buffer_impl.hpp"
#include "../check_state.hpp"
#include "../state_visitor.hpp"
#include "../glsl/impl.hpp"
#include "../common.hpp"
#include "../matrix.hpp"
#include "../split_states.hpp"
#include "../material.hpp"
#include "../glew.hpp"
#include "../fbo_target.hpp"
#include "../convert_primitive.hpp"
#include "../fbo_projection.hpp"
#include "../viewport.hpp"
#include "../viewport_pos.hpp"
#include "../background_dim.hpp"
#include "../caps.hpp"
#include <sge/renderer/caps.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/combine.hpp>
#include <sge/renderer/indices_per_primitive.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/window/instance.hpp>
#include <sge/variant/apply_unary.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/optional_impl.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>
#include <boost/cstdint.hpp>
#include <sstream>

sge::opengl::device::device(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	window::instance_ptr const wnd)
:
	param(param),
	wnd(wnd),
	current_states(
		renderer::state::default_()
	),
	state_(
		param,
		adapter,
		wnd,
		boost::bind(
			&device::reset_viewport,
			this,
			_1
		)
	),
	fbo_active(
		false
	),
	projection_(
		math::matrix::static_<float, 4, 4>::type::identity()
	),
	viewport_mode_(
		renderer::viewport_mode::centered_screen_size
	),
	viewport_(
		renderer::pixel_pos::null(),
		param.mode().size()
	),
	default_target_(
		make_shared_ptr<
			opengl::default_target
		>(
			math::dim::structure_cast<
				target::dim_type
			>(
				screen_size()
			),
			param.mode().bit_depth()
		)
	),
	target_(
		default_target_
	),
	caps_(),
	state_levels()
{
	initialize_glew();

	initialize_vbo();
	initialize_pbo();

	state(
		renderer::state::default_()
	);
	
	projection_internal();

	reset_viewport_default();
	
	target_->bind_me();

	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

void sge::opengl::device::begin_rendering()
{
	glClear(
		clear_bit(renderer::state::bool_::clear_backbuffer)
		| clear_bit(renderer::state::bool_::clear_zbuffer)
		| clear_bit(renderer::state::bool_::clear_stencil));

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glClear failed"),
		sge::renderer::exception
	)
}

sge::renderer::index_buffer_ptr const
sge::opengl::device::create_index_buffer(
	renderer::index::format::type const format,
	renderer::size_type const sz,
	renderer::resource_flags_field const &flags
)
{
	switch(format) {
	case renderer::index::format::i16:
		return renderer::index_buffer_ptr(
			make_shared_ptr<
				opengl::index_buffer<
					boost::uint16_t
				>
			>(
				sz,
				flags
			)
		);
	case renderer::index::format::i32:
		return renderer::index_buffer_ptr(
			make_shared_ptr<
				opengl::index_buffer<
					boost::uint32_t
				>
			>(
				sz,
				flags
			)
		);
	default:
		throw exception(
			SGE_TEXT("Invalid index::format!"));
	}
}

sge::renderer::texture_ptr const
sge::opengl::device::create_texture(
	renderer::texture::dim_type const &dim,
	image::color::format::type const format,
	renderer::filter::texture const &filter,
	renderer::resource_flags_field const &flags
)
{
	return renderer::texture_ptr(
		make_shared_ptr<
			opengl::texture
		>(
			dim,
			format,
			filter,
			flags
		)
	);
}

sge::renderer::vertex_buffer_ptr const
sge::opengl::device::create_vertex_buffer(
	renderer::vf::dynamic_format const &format,
	renderer::size_type const sz,
	renderer::resource_flags_field const &flags
)
{
	return renderer::vertex_buffer_ptr(
		make_shared_ptr<
			opengl::vertex_buffer
		>(
			format,
			sz,
			flags
		)
	);
}

#if 0
const sge::renderer::volume_texture_ptr
sge::opengl::device::create_volume_texture(
	renderer::volume_texture::image_view_array const &src,
	const renderer::texture_filter& filter,
	const renderer::volume_texture::resource_flag_type flags)
{
	/*return renderer::volume_texture_ptr(
		make_shared_ptr<
			volume_texture
		>(
			src,
			filter,
			flags));*/
}
#endif

sge::renderer::cube_texture_ptr const
sge::opengl::device::create_cube_texture(
	renderer::size_type const border_size,
	image::color::format::type const format,
	renderer::filter::texture const &filter,
	renderer::resource_flags_field const &flags
)
{
	return renderer::cube_texture_ptr(
		make_shared_ptr<
			cube_texture
		>(
			border_size,
			format,
			filter,
			flags
		)
	);
}

void sge::opengl::device::end_rendering()
{
	state_.swap_buffers();
}

sge::renderer::caps const
sge::opengl::device::caps() const
{
	if(!caps_)
	{
		caps_.take(
			create_caps()
		);
	}

	return *caps_;
}

sge::window::instance_ptr const
sge::opengl::device::window() const
{
	return wnd;
}

sge::renderer::screen_size const
sge::opengl::device::screen_size() const
{
	return param.mode().size();
}

void sge::opengl::device::render(
	renderer::const_vertex_buffer_ptr const vb,
	renderer::const_index_buffer_ptr const ib,
	renderer::size_type const first_vertex,
	renderer::size_type const num_vertices,
	renderer::indexed_primitive_type::type const ptype,
	renderer::size_type const pcount,
	renderer::size_type const first_index)
{
	if(!vb)
		throw exception(
			SGE_TEXT("vb may not be 0 for renderer::render!"));
	if(!ib)
		throw exception(
			SGE_TEXT("ib may not be 0 for renderer::render for indexed primitives!"));

	vertex_buffer(vb);

	GLenum const prim_type = convert_primitive(ptype);

	index_buffer_base const & gl_ib(
		dynamic_cast<
			index_buffer_base const &
		>(
			*ib
		)
	);

	gl_ib.bind_me();

	glDrawElements(
		prim_type,
		static_cast<GLsizei>(
			renderer::indices_per_primitive(
				ptype
			) * pcount
		),
		gl_ib.gl_format(),
		gl_ib.buffer_offset(
			first_index
		)
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glDrawElements failed"),
		sge::renderer::exception
	)
}

void sge::opengl::device::render(
	renderer::const_vertex_buffer_ptr const vb,
	renderer::size_type const first_vertex,
	renderer::size_type const num_vertices,
	renderer::nonindexed_primitive_type::type const ptype)
{
	if(!vb)
		throw exception(
			SGE_TEXT("vb may not be 0 for renderer::render!"));

	vertex_buffer(vb);

	GLenum const prim_type = convert_primitive(ptype);

	glDrawArrays(
		prim_type,
		static_cast<GLsizei>(first_vertex),
		static_cast<GLint>(num_vertices)
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glDrawArrays failed"),
		sge::renderer::exception
	)
}

void sge::opengl::device::state(
	renderer::state::list const &states)
{
	split_states split(current_states);

	state_visitor const visitor(split);

	BOOST_FOREACH(renderer::state::any const &s, states.values())
	{
		current_states.overwrite(s);

		variant::apply_unary(
			visitor, s
		);
	}
}

void sge::opengl::device::push_state(
	renderer::state::list const &states)
{	
	state_levels.push(
		current_states);

	state(
		renderer::state::combine(
			current_states,
			states
		)
	);
}

void sge::opengl::device::pop_state()
{
	state(state_levels.top());
	state_levels.pop();
}

GLenum sge::opengl::device::clear_bit(
	renderer::state::bool_::trampoline_type const &s) const
{
	return current_states.get(s) ? convert_clear_bit(s) : 0;
}

void sge::opengl::device::material(
	renderer::material const &mat)
{
	opengl::set_material(mat);
}

void sge::opengl::device::viewport(
	renderer::viewport const &v)
{
	viewport_ = v;
	if(fbo_active)
		opengl::viewport(
			v,
			static_cast<
				renderer::screen_unit
			>(
				target_->dim().h()
			)
		);
	else
		reset_viewport_default();
}

void sge::opengl::device::viewport_mode(
	renderer::viewport_mode::type const mode)
{
	viewport_mode_ = mode;	
}

void sge::opengl::device::transform(
	renderer::any_matrix const &matrix)
{
	set_matrix(
		GL_MODELVIEW,
		matrix);
}

void sge::opengl::device::projection(
	renderer::any_matrix const &matrix)
{
	projection_ = matrix;
	projection_internal();
}

void sge::opengl::device::texture_transform(
	renderer::any_matrix const &matrix)
{
	set_matrix(
		GL_TEXTURE,
		matrix);
}

void sge::opengl::device::target(
	renderer::texture_ptr const ntarget)
{
	if(!ntarget)
	{
		target_ = default_target_;
		target_->bind_me();
		fbo_active = false;
		projection_internal();
		reset_viewport_default();
		return;
	}

	shared_ptr<opengl::texture> const p(
		dynamic_pointer_cast<opengl::texture>(
			ntarget
		)
	);
	
	fbo_target_ptr const ftarget = create_target();

	ftarget->bind_texture(p);

	target_ = ftarget;
	fbo_active = true;

	viewport(
		renderer::viewport(
			renderer::pixel_pos::null(),
			math::dim::structure_cast<
				renderer::screen_size
			>(
				p->dim()
			)
		)
	);
	
	projection_internal();
}

sge::renderer::const_target_ptr const
sge::opengl::device::target() const
{
	return target_;
}

void sge::opengl::device::texture(
	renderer::const_texture_base_ptr const tex,
	renderer::stage_type const stage)
{
	set_texture_level(stage);

	disable(GL_TEXTURE_1D);
	disable(GL_TEXTURE_2D);
	//disable(detail::volume_texture_type);
	disable_cube_texture();

	if(!tex)
		return;
	texture_base const &b = dynamic_cast<texture_base const &>(*tex);
	enable(b.type());
	b.bind_me();
}

void sge::opengl::device::enable_light(
	renderer::light_index const index,
	bool const enable_)
{
	GLenum const glindex = convert_light_index(index);
	enable(glindex, enable_);
}

void sge::opengl::device::light(
	renderer::light_index const index,
	renderer::light const &l)
{
	opengl::set_light(
		index,
		l);
}

void sge::opengl::device::texture_stage_op(
	renderer::stage_type const stage,
	renderer::texture_stage_op::type const op,
	renderer::texture_stage_op_value::type const value)
{
	set_texture_stage(stage, op, value);
	set_texture_stage_scale(value);
}

void sge::opengl::device::texture_stage_arg(
	renderer::stage_type const stage,
	renderer::texture_stage_arg::type const arg,
	renderer::texture_stage_arg_value::type const value)
{
	set_texture_stage(stage, arg, value);
}

sge::renderer::glsl::program_ptr const
sge::opengl::device::create_glsl_program(
	renderer::glsl::optional_string const &vs_source,
	renderer::glsl::optional_string const &ps_source)
{
	return	
		vs_source || ps_source
		? glsl::create_program_impl(
			vs_source,
			ps_source
		)
		: no_program;
}

sge::renderer::glsl::program_ptr const
sge::opengl::device::create_glsl_program(
	renderer::glsl::optional_istream const &vs_source,
	renderer::glsl::optional_istream const &ps_source)
{
	// unfortunately opengl can't read out of files directly
	typedef std::basic_ostringstream<
		renderer::glsl::char_type
	> osstream;

	osstream
		vs_stream,
		ps_stream;
	
	if(vs_source)
		vs_stream << vs_source->get().rdbuf();
	if(ps_source)
		ps_stream << ps_source->get().rdbuf();

	return create_glsl_program(
		vs_source
			? vs_stream.str()
			: renderer::glsl::optional_string(),
		ps_source
			? ps_stream.str()
			: renderer::glsl::optional_string()
		);
}

void sge::opengl::device::glsl_program(
	renderer::glsl::program_ptr const prog)
{
	glsl::set_program_impl(prog);
}

void sge::opengl::device::vertex_buffer(
	renderer::const_vertex_buffer_ptr const vb)
{
	opengl::vertex_buffer const &
		ovb = dynamic_cast<opengl::vertex_buffer const &>(
			*vb);
	ovb.set_format();
}

sge::opengl::fbo_target_ptr const
sge::opengl::device::create_target()
{
	return make_shared_ptr<
		fbo_target
	>();
}

void sge::opengl::device::reset_viewport(
	sge::window::dim_type const &wnd_sz)
{
	opengl::viewport(
		renderer::viewport(
			viewport_pos(
				viewport_.pos(),
				wnd_sz,
				screen_size(),
				viewport_mode_
			),
			viewport_.size()
		),
		wnd_sz.h()
	);

	// use viewport_pos to calculate the position of
	// the backbuffer as well but starting with an offset of null
	default_target_->pos(
		viewport_pos(
			renderer::pixel_pos::null(),
			wnd_sz,
			screen_size(),
			viewport_mode_
		)
	);

	default_target_->dim(
		background_dim(
			viewport_mode_,
			wnd_sz,
			screen_size()
		)
	);
}

void sge::opengl::device::reset_viewport_default()
{
	reset_viewport(
		wnd->size()
	);
}

void sge::opengl::device::projection_internal()
{
	set_matrix(
		GL_PROJECTION,
		fbo_active
		? fbo_projection(
			projection_)
		: projection_);
		
}
