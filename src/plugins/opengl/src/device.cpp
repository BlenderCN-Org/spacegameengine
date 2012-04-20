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


#include <sge/opengl/check_state_once.hpp>
#include <sge/opengl/clear.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/create_caps.hpp>
#include <sge/opengl/create_device_state.hpp>
#include <sge/opengl/device.hpp>
#include <sge/opengl/device_state.hpp>
#include <sge/opengl/draw_arrays.hpp>
#include <sge/opengl/draw_elements.hpp>
#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/index_buffer.hpp>
#include <sge/opengl/init_multi_sampling.hpp>
#include <sge/opengl/onscreen_target.hpp>
#include <sge/opengl/set_clip_plane.hpp>
#include <sge/opengl/set_material.hpp>
#include <sge/opengl/set_matrix_and_mode.hpp>
#include <sge/opengl/set_vertex_buffer.hpp>
#include <sge/opengl/set_vertex_declaration.hpp>
#include <sge/opengl/unset_vertex_buffer.hpp>
#include <sge/opengl/vertex_buffer.hpp>
#include <sge/opengl/vertex_declaration.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/convert/clip_plane_index.hpp>
#include <sge/opengl/fbo/create_depth_stencil_surface.hpp>
#include <sge/opengl/fbo/target.hpp>
#include <sge/opengl/glsl/create_geometry_shader.hpp>
#include <sge/opengl/glsl/create_pixel_shader.hpp>
#include <sge/opengl/glsl/create_program.hpp>
#include <sge/opengl/glsl/create_vertex_shader.hpp>
#include <sge/opengl/glsl/set_program.hpp>
#include <sge/opengl/light/enable.hpp>
#include <sge/opengl/light/set.hpp>
#include <sge/opengl/state/apply.hpp>
#include <sge/opengl/state/initial.hpp>
#include <sge/opengl/texture/activate.hpp>
#include <sge/opengl/texture/cube.hpp>
#include <sge/opengl/texture/depth_stencil.hpp>
#include <sge/opengl/texture/optional_type.hpp>
#include <sge/opengl/texture/planar.hpp>
#include <sge/opengl/texture/set_stage_funcs.hpp>
#include <sge/opengl/texture/volume.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/opengl/texture/address_mode/update.hpp>
#include <sge/opengl/texture/filter/update.hpp>
#include <sge/renderer/depth_stencil_surface.hpp>
#include <sge/renderer/optional_target_ref.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/caps/object.hpp>
#include <sge/renderer/glsl/geometry_shader.hpp>
#include <sge/renderer/glsl/pixel_shader.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/vertex_shader.hpp>
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/i32.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/to_clear_flags_field.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>


sge::opengl::device::device(
	renderer::parameters const &_parameters,
	renderer::adapter const _adapter,
	awl::window::object &_window
)
:
	depth_stencil_buffer_(
		_parameters.depth_stencil_buffer()
	),
	current_states_(
		opengl::state::initial()
	),
	context_(),
	state_(
		opengl::create_device_state(
			context_,
			_parameters,
			_adapter,
			_window
		)
	),
	onscreen_target_(
		fcppt::make_unique_ptr<
			opengl::onscreen_target
		>(
			fcppt::ref(
				_window
			)
		)
	),
	fbo_target_(),
	target_(
		onscreen_target_.get()
	),
	glew_init_(),
	caps_(
		opengl::create_caps(
			context_
		)
	),
	state_levels_()
{
	this->state(
		sge::renderer::state::default_()
	);

	target_->bind();

	opengl::init_multi_sampling(
		context_,
		_parameters.samples()
	);
}

sge::opengl::device::~device()
{
}

void
sge::opengl::device::begin_rendering()
{
	state_->begin_rendering();

	this->clear(
		renderer::state::to_clear_flags_field(
			current_states_
		)
	);
}

void
sge::opengl::device::end_rendering()
{
	opengl::check_state_once();

	if(
		!this->fbo_active()
	)
		state_->swap_buffers();
}

void
sge::opengl::device::clear(
	renderer::clear_flags_field const &_flags
)
{
	opengl::clear(
		_flags
	);
}

void
sge::opengl::device::render_indexed(
	renderer::index_buffer const &_ib,
	renderer::first_vertex const _first_vertex,
	renderer::vertex_count const _num_vertices,
	renderer::indexed_primitive_type::type const _ptype,
	renderer::primitive_count const _pcount,
	renderer::first_index const _first_index
)
{
	opengl::draw_elements(
		context_,
		_ib,
		_first_vertex,
		_num_vertices,
		_ptype,
		_pcount,
		_first_index
	);
}

void
sge::opengl::device::render_nonindexed(
	renderer::first_vertex const _first_vertex,
	renderer::vertex_count const _num_vertices,
	renderer::nonindexed_primitive_type::type const _ptype
)
{
	opengl::draw_arrays(
		_first_vertex,
		_num_vertices,
		_ptype
	);
}

void
sge::opengl::device::activate_vertex_buffer(
	renderer::vertex_buffer const &_vertex_buffer
)
{
	opengl::set_vertex_buffer(
		context_,
		_vertex_buffer
	);
}

void
sge::opengl::device::deactivate_vertex_buffer(
	renderer::vertex_buffer const &_vertex_buffer
)
{
	opengl::unset_vertex_buffer(
		context_,
		_vertex_buffer
	);
}

void
sge::opengl::device::vertex_declaration(
	renderer::const_optional_vertex_declaration_ref const &_vertex_declaration
)
{
	opengl::set_vertex_declaration(
		context_,
		_vertex_declaration
	);
}

void
sge::opengl::device::state(
	renderer::state::list const &_states
)
{
	opengl::state::apply(
		context_,
		current_states_,
		_states,
		depth_stencil_buffer_
	);
}

void
sge::opengl::device::push_state(
	renderer::state::list const &_states
)
{
	state_levels_.push(
		current_states_
	);

	this->state(
		_states
	);
}

void
sge::opengl::device::pop_state()
{
	this->state(
		state_levels_.top()
	);

	state_levels_.pop();
}

void
sge::opengl::device::material(
	renderer::material const &_mat
)
{
	opengl::set_material(
		_mat
	);
}

void
sge::opengl::device::enable_light(
	renderer::light::index const _index,
	bool const _enable
)
{
	opengl::light::enable(
		_index,
		_enable
	);
}

void
sge::opengl::device::light(
	renderer::light::index const _index,
	renderer::light::object const &_light
)
{
	opengl::light::set(
		_index,
		_light
	);
}

void
sge::opengl::device::enable_clip_plane(
	renderer::clip_plane_index const _index,
	bool const _enable
)
{
	opengl::enable_bool(
		convert::clip_plane_index(
			_index
		),
		_enable
	);
}

void
sge::opengl::device::clip_plane(
	renderer::clip_plane_index const _index,
	renderer::clip_plane const &_clip_plane
)
{
	opengl::set_clip_plane(
		_index,
		_clip_plane
	);
}

void
sge::opengl::device::texture_stage_op(
	renderer::texture::stage const _stage,
	renderer::texture::stage_op::type const _op,
	renderer::texture::stage_op_value::type const _value
)
{
	opengl::texture::set_stage_funcs(
		context_,
		_stage,
		_op,
		_value
	);
}

void
sge::opengl::device::texture_stage_arg(
	renderer::texture::stage const _stage,
	renderer::texture::stage_arg::type const _arg,
	renderer::texture::stage_arg_value::type const _value
)
{
	opengl::texture::set_stage_funcs(
		context_,
		_stage,
		_arg,
		_value
	);
}

void
sge::opengl::device::texture_filter(
	renderer::texture::filter::object const &_filter,
	renderer::texture::stage const _stage
)
{
	opengl::texture::filter::update(
		context_,
		_stage,
		_filter
	);
}

void
sge::opengl::device::texture_address_mode_s(
	renderer::texture::address_mode_s const _mode,
	renderer::texture::stage const _stage
)
{
	opengl::texture::address_mode::update(
		context_,
		_mode,
		_stage
	);
}

void
sge::opengl::device::texture_address_mode_t(
	renderer::texture::address_mode_t const _mode,
	renderer::texture::stage const _stage
)
{
	opengl::texture::address_mode::update(
		context_,
		_mode,
		_stage
	);
}

void
sge::opengl::device::texture_address_mode_u(
	renderer::texture::address_mode_u const _mode,
	renderer::texture::stage const _stage
)
{
	opengl::texture::address_mode::update(
		context_,
		_mode,
		_stage
	);
}

void
sge::opengl::device::texture(
	renderer::texture::const_optional_base_ref const &_texture,
	renderer::texture::stage const _stage
)
{
	opengl::texture::activate(
		context_,
		_texture,
		_stage
	);
}

void
sge::opengl::device::transform(
	renderer::matrix_mode::type const _mode,
	renderer::matrix4 const &_matrix
)
{
	opengl::set_matrix_and_mode(
		context_,
		_mode,
		_matrix
	);
}

void
sge::opengl::device::target(
	renderer::optional_target_ref const &_target
)
{
	fbo_target_ =
		_target.has_value()
		?
			&dynamic_cast<
				opengl::fbo::target &
			>(
				*_target
			)
		:
			fcppt::null_ptr()
		;

	target_->unbind();

	target_ =
		_target.has_value()
		?
			static_cast<
				opengl::target_base *
			>(
				fbo_target_
			)
		:
			static_cast<
				opengl::target_base *
			>(
				onscreen_target_.get()
			);

	target_->bind();
}

sge::renderer::glsl::program_unique_ptr
sge::opengl::device::create_glsl_program()
{
	return
		glsl::create_program(
			context_
		);
}

sge::renderer::glsl::vertex_shader_unique_ptr
sge::opengl::device::create_glsl_vertex_shader(
	renderer::glsl::string const &_source
)
{
	return
		glsl::create_vertex_shader(
			context_,
			_source
		);
}

sge::renderer::glsl::pixel_shader_unique_ptr
sge::opengl::device::create_glsl_pixel_shader(
	renderer::glsl::string const &_source
)
{
	return
		glsl::create_pixel_shader(
			context_,
			_source
		);
}

sge::renderer::glsl::geometry_shader_unique_ptr
sge::opengl::device::create_glsl_geometry_shader(
	renderer::glsl::string const &_source
)
{
	return
		glsl::create_geometry_shader(
			context_,
			_source
		);
}

void
sge::opengl::device::glsl_program(
	renderer::glsl::const_optional_program_ref const &_program
)
{
	glsl::set_program(
		context_,
		_program
	);
}

sge::renderer::optional_target_ref const
sge::opengl::device::target() const
{
	return
		this->fbo_active()
		?
			renderer::optional_target_ref(
				*fbo_target_
			)
		:
			renderer::optional_target_ref()
		;
}

sge::renderer::target_unique_ptr
sge::opengl::device::create_target()
{
	return
		sge::renderer::target_unique_ptr(
			fcppt::make_unique_ptr<
				fbo::target
			>(
				fcppt::ref(
					context_
				)
			)
		);
}

sge::renderer::texture::planar_unique_ptr
sge::opengl::device::create_planar_texture(
	renderer::texture::planar_parameters const &_params
)
{
	return
		renderer::texture::planar_unique_ptr(
			fcppt::make_unique_ptr<
				opengl::texture::planar
			>(
				fcppt::ref(
					context_
				),
				fcppt::cref(
					_params
				),
				opengl::texture::optional_type()
			)
		);
}

sge::renderer::texture::depth_stencil_unique_ptr
sge::opengl::device::create_depth_stencil_texture(
	renderer::texture::depth_stencil_parameters const &_params
)
{
	return
		renderer::texture::depth_stencil_unique_ptr(
			fcppt::make_unique_ptr<
				opengl::texture::depth_stencil
			>(
				fcppt::ref(
					context_
				),
				fcppt::cref(
					_params
				)
			)
		);
}

sge::renderer::depth_stencil_surface_unique_ptr
sge::opengl::device::create_depth_stencil_surface(
	renderer::dim2 const &_dim,
	renderer::depth_stencil_format::type const _type
)
{
	return
		renderer::depth_stencil_surface_unique_ptr(
			opengl::fbo::create_depth_stencil_surface(
				context_,
				_dim,
				_type
			)
		);
}

sge::renderer::texture::volume_unique_ptr
sge::opengl::device::create_volume_texture(
	renderer::texture::volume_parameters const &_param
)
{
	if(
		!context::use<
			opengl::texture::volume_context
		>(
			context_
		).have_volume_texture()
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("volume texture"),
			FCPPT_TEXT("1.2"),
			FCPPT_TEXT("")
		);

	return
		renderer::texture::volume_unique_ptr(
			fcppt::make_unique_ptr<
				opengl::texture::volume
			>(
				fcppt::ref(
					context_
				),
				fcppt::cref(
					_param
				)
			)
		);
}

sge::renderer::texture::cube_unique_ptr
sge::opengl::device::create_cube_texture(
	renderer::texture::cube_parameters const &_param
)
{
	return
		renderer::texture::cube_unique_ptr(
			fcppt::make_unique_ptr<
				opengl::texture::cube
			>(
				fcppt::ref(
					context_
				),
				fcppt::cref(
					_param
				)
			)
		);
}

sge::renderer::vertex_declaration_unique_ptr
sge::opengl::device::create_vertex_declaration(
	renderer::vf::dynamic::format const &_format
)
{
	return
		renderer::vertex_declaration_unique_ptr(
			fcppt::make_unique_ptr<
				opengl::vertex_declaration
			>(
				fcppt::ref(
					context_
				),
				fcppt::cref(
					_format
				)
			)
		);
}

sge::renderer::vertex_buffer_unique_ptr
sge::opengl::device::create_vertex_buffer(
	renderer::vertex_declaration const &_declaration,
	renderer::vf::dynamic::part_index const _part,
	renderer::vertex_count const _size,
	renderer::resource_flags_field const &_flags
)
{
	return
		renderer::vertex_buffer_unique_ptr(
			fcppt::make_unique_ptr<
				opengl::vertex_buffer
			>(
				fcppt::ref(
					context_
				),
				_part,
				dynamic_cast<
					opengl::vertex_declaration const &
				>(
					_declaration
				).format_part(
					_part
				),
				_size,
				_flags
			)
		);
}

sge::renderer::index_buffer_unique_ptr
sge::opengl::device::create_index_buffer(
	renderer::index::dynamic::format::type const _format,
	renderer::index_count const _size,
	renderer::resource_flags_field const &_flags
)
{
	return
		renderer::index_buffer_unique_ptr(
			fcppt::make_unique_ptr<
				opengl::index_buffer
			>(
				fcppt::ref(
					context_
				),
				_format,
				_size,
				_flags
			)
		);
}

sge::renderer::onscreen_target &
sge::opengl::device::onscreen_target() const
{
	return *onscreen_target_;
}

sge::renderer::caps::object const &
sge::opengl::device::caps() const
{
	return *caps_;
}

bool
sge::opengl::device::fbo_active() const
{
	return
		fbo_target_
		!=
		fcppt::null_ptr();
}
