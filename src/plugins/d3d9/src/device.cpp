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


#include <sge/d3d9/create_caps.hpp>
#include <sge/d3d9/create_device.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device.hpp>
#include <sge/d3d9/index_buffer.hpp>
#include <sge/d3d9/multi_sample_quality.hpp>
#include <sge/d3d9/needs_reset.hpp>
#include <sge/d3d9/offscreen_target.hpp>
#include <sge/d3d9/onscreen_target.hpp>
#include <sge/d3d9/vertex_buffer.hpp>
#include <sge/d3d9/vertex_declaration.hpp>
#include <sge/d3d9/devicefuncs/begin_scene.hpp>
#include <sge/d3d9/devicefuncs/clear.hpp>
#include <sge/d3d9/devicefuncs/create_depth_stencil_surface.hpp>
#include <sge/d3d9/devicefuncs/draw_indexed_primitive.hpp>
#include <sge/d3d9/devicefuncs/draw_primitive.hpp>
#include <sge/d3d9/devicefuncs/end_scene.hpp>
#include <sge/d3d9/devicefuncs/light_enable.hpp>
#include <sge/d3d9/devicefuncs/present.hpp>
#include <sge/d3d9/devicefuncs/reset.hpp>
#include <sge/d3d9/devicefuncs/set_clip_plane.hpp>
#include <sge/d3d9/devicefuncs/set_index_buffer.hpp>
#include <sge/d3d9/devicefuncs/set_light.hpp>
#include <sge/d3d9/devicefuncs/set_material.hpp>
#include <sge/d3d9/devicefuncs/set_render_state.hpp>
#include <sge/d3d9/devicefuncs/set_stream_source.hpp>
#include <sge/d3d9/devicefuncs/set_transform.hpp>
#include <sge/d3d9/devicefuncs/set_vertex_declaration.hpp>
#include <sge/d3d9/devicefuncs/texture_stage_arg.hpp>
#include <sge/d3d9/devicefuncs/texture_stage_op.hpp>
#include <sge/d3d9/parameters/create.hpp>
#include <sge/d3d9/state/apply.hpp>
#include <sge/d3d9/state/device.hpp>
#include <sge/d3d9/surface/depth_stencil.hpp>
#include <sge/d3d9/surface/depth_stencil_native.hpp>
#include <sge/d3d9/texture/address_mode.hpp>
#include <sge/d3d9/texture/cube.hpp>
#include <sge/d3d9/texture/depth_stencil.hpp>
#include <sge/d3d9/texture/init_state.hpp>
#include <sge/d3d9/texture/planar.hpp>
#include <sge/d3d9/texture/set.hpp>
#include <sge/d3d9/texture/volume.hpp>
#include <sge/d3d9/texture/filter/set.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/optional_target.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/caps/object.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/to_clear_flags_field.hpp>
#include <awl/window/instance.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/chrono/milliseconds.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/time/sleep_any.hpp>


sge::d3d9::device::device(
	IDirect3D9 *const _system,
	renderer::adapter const _adapter,
	renderer::parameters const &_parameters,
	awl::window::instance &_window
)
:
	present_parameters_(
		d3d9::parameters::create(
			_parameters,
			_window
		)
	),
	device_(
		d3d9::create_device(
			_system,
			_adapter,
			present_parameters_
		)
	),
	caps_(
		d3d9::create_caps(
			_system,
			_adapter
		)
	),
	resources_(),
	onscreen_target_(
		fcppt::make_unique_ptr<
			d3d9::onscreen_target
		>(
			device_.get(),
			sge::renderer::viewport(
				sge::renderer::pixel_rect(
					sge::renderer::pixel_rect::vector::null(),
					fcppt::math::dim::structure_cast<
						sge::renderer::pixel_rect::dim
					>(
						_window.size()
					)
				)
			),
			fcppt::ref(
				resources_
			)
		)
	),
	device_state_()
{
	this->init();
}

sge::d3d9::device::~device()
{
}

void
sge::d3d9::device::begin_rendering()
{
	this->clear(
		sge::renderer::state::to_clear_flags_field(
			device_state_->current()
		)
	);

	devicefuncs::begin_scene(
		device_.get()
	);
}

void
sge::d3d9::device::end_rendering()
{
	devicefuncs::end_scene(
		device_.get()
	);

	if(
		!devicefuncs::present(
			device_.get()
		)
	)
		this->reset();
}

void
sge::d3d9::device::clear(
	renderer::clear_flags_field const &_flags
)
{
	devicefuncs::clear(
		device_.get(),
		_flags,
		device_state_->clear()
	);
}

void
sge::d3d9::device::render_indexed(
	renderer::index_buffer const &_index_buffer,
	renderer::first_vertex const _first_vertex,
	renderer::vertex_count const _num_vertices,
	renderer::indexed_primitive_type::type const _primitive_type,
	renderer::primitive_count const _primitive_count,
	renderer::first_index const _first_index
)
{
	devicefuncs::set_index_buffer(
		device_.get(),
		_index_buffer
	);

	devicefuncs::draw_indexed_primitive(
		device_.get(),
		_first_vertex,
		_num_vertices,
		_primitive_type,
		_primitive_count,
		_first_index
	);

}

void
sge::d3d9::device::render_nonindexed(
	renderer::first_vertex const _first_vertex,
	renderer::vertex_count const _num_vertices,
	renderer::nonindexed_primitive_type::type const _primitive_type
)
{
	devicefuncs::draw_primitive(
		device_.get(),
		_first_vertex,
		_num_vertices,
		_primitive_type
	);
}

void
sge::d3d9::device::activate_vertex_buffer(
	renderer::vertex_buffer const &_buffer
)
{
	d3d9::devicefuncs::set_stream_source(
		device_.get(),
		_buffer
	);
}

void
sge::d3d9::device::deactivate_vertex_buffer(
	renderer::vertex_buffer const &_buffer
)
{
}

void
sge::d3d9::device::vertex_declaration(
	renderer::const_optional_vertex_declaration const &_declaration
)
{
	if(
		!_declaration
	)
		return;

	devicefuncs::set_vertex_declaration(
		device_.get(),
		*_declaration
	);
}

void
sge::d3d9::device::state(
	renderer::state::list const &_states
)
{
	d3d9::state::apply(
		device_.get(),
		device_state_->clear(),
		device_state_->current(),
		_states
	);
}

void
sge::d3d9::device::push_state(
	renderer::state::list const &_states
)
{
	device_state_->push();

	this->state(
		_states
	);
}

void
sge::d3d9::device::pop_state()
{
	this->state(
		device_state_->pop()
	);
}
void
sge::d3d9::device::material(
	renderer::material const &_material
)
{
	d3d9::devicefuncs::set_material(
		device_.get(),
		_material
	);
}

void
sge::d3d9::device::enable_light(
	renderer::light::index const _index,
	bool const _enable
)
{
	devicefuncs::light_enable(
		device_.get(),
		_index,
		_enable
	);
}

void
sge::d3d9::device::light(
	renderer::light::index const _index,
	renderer::light::object const &_light
)
{
	devicefuncs::set_light(
		device_.get(),
		_index,
		_light
	);
}

void
sge::d3d9::device::enable_clip_plane(
	renderer::clip_plane_index const _index,
	bool const _enable
)
{
	device_state_->clip_plane().set(
		_index,
		_enable
	);

	devicefuncs::set_render_state(
		device_.get(),
		D3DRS_CLIPPLANEENABLE,
		device_state_->clip_plane().dword()
	);
}

void
sge::d3d9::device::clip_plane(
	renderer::clip_plane_index const _index,
	renderer::clip_plane const &_plane
)
{
	devicefuncs::set_clip_plane(
		device_.get(),
		_index,
		_plane
	);
}

void
sge::d3d9::device::texture_stage_op(
	renderer::texture::stage const _stage,
	renderer::texture::stage_op::type const _type,
	renderer::texture::stage_op_value::type const _arg
)
{
	devicefuncs::texture_stage_op(
		device_.get(),
		_stage,
		_type,
		_arg
	);
}

void
sge::d3d9::device::texture_stage_arg(
	renderer::texture::stage const _stage,
	renderer::texture::stage_arg::type const _type,
	renderer::texture::stage_arg_value::type const _arg
)
{
	devicefuncs::texture_stage_arg(
		device_.get(),
		_stage,
		_type,
		_arg
	);
}

void
sge::d3d9::device::texture(
	renderer::texture::const_optional_base const &_texture,
	renderer::texture::stage const _stage
)
{
	texture::set(
		device_.get(),
		_stage,
		_texture
	);
}

void
sge::d3d9::device::texture_filter(
	renderer::texture::filter::object const &_filter,
	renderer::texture::stage const _stage
)
{
	texture::filter::set(
		device_.get(),
		_stage,
		_filter
	);
}

void
sge::d3d9::device::texture_address_mode_s(
	renderer::texture::address_mode_s const _mode,
	renderer::texture::stage const _stage
)
{
	texture::address_mode(
		device_.get(),
		_stage,
		_mode
	);
}

void
sge::d3d9::device::texture_address_mode_t(
	renderer::texture::address_mode_t const _mode,
	renderer::texture::stage const _stage
)
{
	texture::address_mode(
		device_.get(),
		_stage,
		_mode
	);
}

void
sge::d3d9::device::texture_address_mode_u(
	renderer::texture::address_mode_u const _mode,
	renderer::texture::stage const _stage
)
{
	texture::address_mode(
		device_.get(),
		_stage,
		_mode
	);
}

void
sge::d3d9::device::transform(
	renderer::matrix_mode::type const _mode,
	renderer::matrix4 const &_matrix
)
{
	d3d9::devicefuncs::set_transform(
		device_.get(),
		_mode,
		_matrix
	);
}

void
sge::d3d9::device::target(
	renderer::optional_target const &_target
)
{
	device_state_->target(
		_target
	);
}

sge::renderer::glsl::program_ptr const
sge::d3d9::device::create_glsl_program()
{
	throw sge::renderer::exception(
		FCPPT_TEXT("glsl not supported for d3d9!")
	);
}

sge::renderer::glsl::vertex_shader_ptr const
sge::d3d9::device::create_glsl_vertex_shader(
	renderer::glsl::string const &
)
{
	throw sge::renderer::exception(
		FCPPT_TEXT("glsl not supported for d3d9!")
	);
}

sge::renderer::glsl::pixel_shader_ptr const
sge::d3d9::device::create_glsl_pixel_shader(
	renderer::glsl::string const &
)
{
	throw sge::renderer::exception(
		FCPPT_TEXT("glsl not supported for d3d9!")
	);
}

sge::renderer::glsl::geometry_shader_ptr const
sge::d3d9::device::create_glsl_geometry_shader(
	renderer::glsl::string const &
)
{
	throw sge::renderer::exception(
		FCPPT_TEXT("glsl not supported for d3d9!")
	);
}

void
sge::d3d9::device::glsl_program(
	renderer::glsl::const_optional_program const &
)
{
	throw sge::renderer::exception(
		FCPPT_TEXT("glsl not supported for d3d9!")
	);
}

sge::renderer::target_ptr const
sge::d3d9::device::create_target()
{
	return
		fcppt::make_shared_ptr<
			d3d9::offscreen_target
		>(
			device_.get()
		);
}

sge::renderer::texture::planar_ptr const
sge::d3d9::device::create_planar_texture(
	renderer::texture::planar_parameters const &_param
)
{
	return
		this->add_resource<
			d3d9::texture::planar
		>(
			fcppt::make_shared_ptr<
				d3d9::texture::planar
			>(
				device_.get(),
				_param
			)
		);
}

sge::renderer::texture::depth_stencil_ptr const
sge::d3d9::device::create_depth_stencil_texture(
	renderer::texture::depth_stencil_parameters const &_params
)
{
	return
		sge::renderer::texture::depth_stencil_ptr();
#if 0
	return
		this->add_resource<
			d3d9::texture::depth_stencil
		>(
			fcppt::make_shared_ptr<
				d3d9::texture::depth_stencil
			>(
				device_.get(),
				_params
			)
		);
#endif
}

sge::renderer::depth_stencil_surface_ptr const
sge::d3d9::device::create_depth_stencil_surface(
	renderer::dim2 const &_dim,
	renderer::depth_stencil_format::type const _format
)
{
	return
		this->add_resource<
			d3d9::surface::depth_stencil
		>(
			fcppt::make_shared_ptr<
				d3d9::surface::depth_stencil
			>(
				fcppt::make_unique_ptr<
					d3d9::surface::depth_stencil_native
				>(
					device_.get(),
					_dim,
					_format,
					present_parameters_.MultiSampleType,
					d3d9::multi_sample_quality(
						present_parameters_.MultiSampleQuality
					)
				),
				d3d9::needs_reset::yes
			)
		);
}

sge::renderer::texture::volume_ptr const
sge::d3d9::device::create_volume_texture(
	renderer::texture::volume_parameters const &_param
)
{
	return
		this->add_resource<
			d3d9::texture::volume
		>(
			fcppt::make_shared_ptr<
				d3d9::texture::volume
			>(
				device_.get(),
				_param
			)
		);
}

sge::renderer::texture::cube_ptr const
sge::d3d9::device::create_cube_texture(
	renderer::texture::cube_parameters const &_param
)
{
	return
		this->add_resource<
			d3d9::texture::cube
		>(
			fcppt::make_shared_ptr<
				d3d9::texture::cube
			>(
				device_.get(),
				_param
			)
		);
}

sge::renderer::vertex_declaration_ptr const
sge::d3d9::device::create_vertex_declaration(
	renderer::vf::dynamic::format const &_format
)
{
	return
		fcppt::make_shared_ptr<
			d3d9::vertex_declaration
		>(
			device_.get(),
			_format
		);
}

sge::renderer::vertex_buffer_ptr const
sge::d3d9::device::create_vertex_buffer(
	renderer::vertex_declaration const &_declaration,
	renderer::vf::dynamic::part_index const _part,
	renderer::vertex_count const _size,
	renderer::resource_flags_field const &_resource_flags
)
{
	return
		this->add_resource<
			d3d9::vertex_buffer
		>(
			fcppt::make_shared_ptr<
				d3d9::vertex_buffer
			>(
				device_.get(),
				dynamic_cast<
					d3d9::vertex_declaration const &
				>(
					_declaration
				).format().parts().at(
					_part.get()
				),
				_part,
				_size,
				_resource_flags
			)
		);
}

sge::renderer::index_buffer_ptr const
sge::d3d9::device::create_index_buffer(
	renderer::index::dynamic::format::type const _format,
	renderer::index_count const _size,
	renderer::resource_flags_field const &_resource_flags
)
{
	return
		this->add_resource<
			d3d9::index_buffer
		>(
			fcppt::make_shared_ptr<
				d3d9::index_buffer
			>(
				device_.get(),
				_format,
				_size,
				_resource_flags
			)
		);
}

sge::renderer::onscreen_target &
sge::d3d9::device::onscreen_target() const
{
	return *onscreen_target_;
}

sge::renderer::optional_target const
sge::d3d9::device::target() const
{
	return device_state_->target();
}

sge::renderer::caps::object const &
sge::d3d9::device::caps() const
{
	return *caps_;
}

template<
	typename Ptr
>
fcppt::shared_ptr<
	Ptr
> const
sge::d3d9::device::add_resource(
	fcppt::shared_ptr<
		Ptr
	> const _ptr
)
{
	resources_.add(
		*_ptr
	);

	return _ptr;
}

void
sge::d3d9::device::init()
{
	device_state_.take(
		fcppt::make_unique_ptr<
			d3d9::state::device
		>(
			fcppt::ref(
				*onscreen_target_
			)
		)
	);

	this->state(
		sge::renderer::state::default_()
	);

	sge::d3d9::texture::init_state(
		device_.get(),
		caps_->texture_stages()
	);
}

void
sge::d3d9::device::reinit()
{
	this->init();

	resources_.reinit();
}

void
sge::d3d9::device::release()
{
	resources_.release();
}

void
sge::d3d9::device::reset()
{
	this->release();

	while(
		device_->TestCooperativeLevel()
		== D3DERR_DEVICELOST
		||
		!d3d9::devicefuncs::reset(
			device_.get(),
			present_parameters_
		)
	)
		fcppt::time::sleep_any(
			fcppt::chrono::milliseconds(
				1
			)
		);

	this->reinit();
}
