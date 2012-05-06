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
#include <sge/d3d9/device.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/index_buffer.hpp>
#include <sge/d3d9/multi_sample_quality.hpp>
#include <sge/d3d9/needs_reset.hpp>
#include <sge/d3d9/resource_manager.hpp>
#include <sge/d3d9/vertex_buffer.hpp>
#include <sge/d3d9/vertex_declaration.hpp>
#include <sge/d3d9/devicefuncs/begin_scene.hpp>
#include <sge/d3d9/devicefuncs/end_scene.hpp>
#include <sge/d3d9/devicefuncs/present.hpp>
#include <sge/d3d9/devicefuncs/reset.hpp>
#include <sge/d3d9/parameters/create.hpp>
#include <sge/d3d9/render_context/create.hpp>
#include <sge/d3d9/surface/depth_stencil.hpp>
#include <sge/d3d9/surface/depth_stencil_native.hpp>
#include <sge/d3d9/target/offscreen.hpp>
#include <sge/d3d9/target/onscreen.hpp>
#include <sge/d3d9/texture/cube.hpp>
#include <sge/d3d9/texture/planar.hpp>
#include <sge/d3d9/texture/volume.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface_unique_ptr.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/index_buffer_unique_ptr.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/vertex_buffer_unique_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_unique_ptr.hpp>
#include <sge/renderer/caps/object.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/context/object_unique_ptr.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/glsl/geometry_shader_unique_ptr.hpp>
#include <sge/renderer/glsl/pixel_shader_unique_ptr.hpp>
#include <sge/renderer/glsl/program_unique_ptr.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/vertex_shader_unique_ptr.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/renderer/target/onscreen_fwd.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_unique_ptr.hpp>
#include <sge/renderer/texture/depth_stencil.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_unique_ptr.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <sge/renderer/vf/dynamic/format_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <awl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/move.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/time/sleep_any.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <fcppt/config/external_end.hpp>


#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/profile/object_unique_ptr.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/d3d9/cg/profile/create.hpp>
#include <sge/d3d9/cg/program/create_loaded.hpp>
#include <sge/d3d9/cg/program/optimal_options.hpp>
#include <sge/d3d9/cg/texture/create_loaded.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#endif


sge::d3d9::device::device(
	IDirect3D9 *const _system,
	sge::renderer::adapter const _adapter,
	sge::renderer::parameters const &_parameters,
	awl::window::object &_window
)
:
	sge::renderer::device(),
	present_parameters_(
		sge::d3d9::parameters::create(
			_parameters,
			_window
		)
	),
	device_(
		sge::d3d9::create_device(
			_system,
			_adapter,
			present_parameters_
		)
	),
	caps_(
		sge::d3d9::create_caps(
			_system,
			_adapter
		)
	),
	resources_(),
	onscreen_target_(
		fcppt::make_unique_ptr<
			sge::d3d9::target::onscreen
		>(
			device_.get(),
			sge::renderer::target::viewport(
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
	)
{
}

sge::d3d9::device::~device()
{
}

sge::renderer::context::object_unique_ptr
sge::d3d9::device::begin_rendering(
	sge::renderer::target::base &_target
)
{
	sge::d3d9::devicefuncs::begin_scene(
		device_.get()
	);

	return
		sge::d3d9::render_context::create(
			device_.get(),
			_target,
			caps_->texture_stages()
		);
}

void
sge::d3d9::device::end_rendering(
	sge::renderer::context::object &
)
{
	sge::d3d9::devicefuncs::end_scene(
		device_.get()
	);

	if(
		!sge::d3d9::devicefuncs::present(
			device_.get()
		)
	)
		this->reset();
}

sge::renderer::glsl::program_unique_ptr
sge::d3d9::device::create_glsl_program()
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("No GLSL support")
	);
}

sge::renderer::glsl::vertex_shader_unique_ptr
sge::d3d9::device::create_glsl_vertex_shader(
	renderer::glsl::string const &
)
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("No GLSL support")
	);
}

sge::renderer::glsl::pixel_shader_unique_ptr
sge::d3d9::device::create_glsl_pixel_shader(
	renderer::glsl::string const &
)
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("No GLSL support")
	);
}

sge::renderer::glsl::geometry_shader_unique_ptr
sge::d3d9::device::create_glsl_geometry_shader(
	renderer::glsl::string const &
)
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("No GLSL support")
	);
}

sge::renderer::target::offscreen_unique_ptr
sge::d3d9::device::create_target()
{
	return
		sge::renderer::target::offscreen_unique_ptr(
			fcppt::make_unique_ptr<
				sge::d3d9::target::offscreen
			>(
				device_.get()
			)
		);
}

sge::renderer::texture::planar_unique_ptr
sge::d3d9::device::create_planar_texture(
	sge::renderer::texture::planar_parameters const &_param
)
{
	return
		sge::renderer::texture::planar_unique_ptr(
			this->add_resource<
				sge::d3d9::texture::planar
			>(
				fcppt::make_unique_ptr<
					sge::d3d9::texture::planar
				>(
					device_.get(),
					_param
				)
			)
		);
}

sge::renderer::texture::depth_stencil_unique_ptr
sge::d3d9::device::create_depth_stencil_texture(
	sge::renderer::texture::depth_stencil_parameters const &_params
)
{
	return
		sge::renderer::texture::depth_stencil_unique_ptr();
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

sge::renderer::depth_stencil_surface_unique_ptr
sge::d3d9::device::create_depth_stencil_surface(
	sge::renderer::dim2 const &_dim,
	sge::renderer::depth_stencil_format::type const _format
)
{
	return
		sge::renderer::depth_stencil_surface_unique_ptr(
			this->add_resource<
				sge::d3d9::surface::depth_stencil
			>(
				fcppt::make_unique_ptr<
					sge::d3d9::surface::depth_stencil
				>(
					fcppt::make_unique_ptr<
						sge::d3d9::surface::depth_stencil_native
					>(
						device_.get(),
						_dim,
						_format,
						present_parameters_.MultiSampleType,
						sge::d3d9::multi_sample_quality(
							present_parameters_.MultiSampleQuality
						)
					),
					sge::d3d9::needs_reset::yes
				)
			)
		);
}

sge::renderer::texture::volume_unique_ptr
sge::d3d9::device::create_volume_texture(
	sge::renderer::texture::volume_parameters const &_param
)
{
	return
		sge::renderer::texture::volume_unique_ptr(
			this->add_resource<
				sge::d3d9::texture::volume
			>(
				fcppt::make_unique_ptr<
					sge::d3d9::texture::volume
				>(
					device_.get(),
					_param
				)
			)
		);
}

sge::renderer::texture::cube_unique_ptr
sge::d3d9::device::create_cube_texture(
	sge::renderer::texture::cube_parameters const &_param
)
{
	return
		sge::renderer::texture::cube_unique_ptr(
			this->add_resource<
				sge::d3d9::texture::cube
			>(
				fcppt::make_unique_ptr<
					sge::d3d9::texture::cube
				>(
					device_.get(),
					_param
				)
			)
		);
}

sge::renderer::vertex_declaration_unique_ptr
sge::d3d9::device::create_vertex_declaration(
	sge::renderer::vf::dynamic::format const &_format
)
{
	return
		sge::renderer::vertex_declaration_unique_ptr(
			fcppt::make_unique_ptr<
				sge::d3d9::vertex_declaration
			>(
				device_.get(),
				_format
			)
		);
}

sge::renderer::vertex_buffer_unique_ptr
sge::d3d9::device::create_vertex_buffer(
	sge::renderer::vertex_declaration const &_declaration,
	sge::renderer::vf::dynamic::part_index const _part,
	sge::renderer::vertex_count const _size,
	sge::renderer::resource_flags_field const &_resource_flags
)
{
	return
		sge::renderer::vertex_buffer_unique_ptr(
			this->add_resource<
				sge::d3d9::vertex_buffer
			>(
				fcppt::make_unique_ptr<
					sge::d3d9::vertex_buffer
				>(
					device_.get(),
					dynamic_cast<
						sge::d3d9::vertex_declaration const &
					>(
						_declaration
					).format().parts().at(
						_part.get()
					),
					_part,
					_size,
					_resource_flags
				)
			)
		);
}

sge::renderer::index_buffer_unique_ptr
sge::d3d9::device::create_index_buffer(
	sge::renderer::index::dynamic::format::type const _format,
	sge::renderer::index_count const _size,
	sge::renderer::resource_flags_field const &_resource_flags
)
{
	return
		sge::renderer::index_buffer_unique_ptr(
			this->add_resource<
				sge::d3d9::index_buffer
			>(
				fcppt::make_unique_ptr<
					sge::d3d9::index_buffer
				>(
					device_.get(),
					_format,
					_size,
					_resource_flags
				)
			)
		);
}

#if defined(SGE_RENDERER_HAVE_CG)
sge::cg::profile::object_unique_ptr
sge::d3d9::device::create_cg_profile(
	sge::cg::profile::shader_type::type const _shader_type
)
{
	return
		sge::d3d9::cg::profile::create(
			device_.get(),
			_shader_type
		);
}

sge::cg::program::compile_options const
sge::d3d9::device::cg_compile_options(
	sge::cg::context::object const &,
	sge::cg::profile::object const &_profile
)
{
	return
		sge::d3d9::cg::program::optimal_options(
			device_.get(),
			_profile
		);
}

sge::renderer::cg::loaded_program_unique_ptr
sge::d3d9::device::load_cg_program(
	sge::cg::program::object &_program
)
{
	return
		sge::d3d9::cg::program::create_loaded(
			device_.get(),
			_program
		);
}

sge::renderer::cg::loaded_texture_unique_ptr
sge::d3d9::device::load_cg_texture(
	sge::cg::parameter::object const &_parameter,
	sge::renderer::texture::base &_texture
)
{
	return
		sge::d3d9::cg::texture::create_loaded(
			device_.get(),
			_parameter,
			_texture,
			caps_->texture_stages()
		);
}
#endif

sge::renderer::target::onscreen &
sge::d3d9::device::onscreen_target() const
{
	return *onscreen_target_;
}

sge::renderer::caps::object const &
sge::d3d9::device::caps() const
{
	return *caps_;
}

template<
	typename Ptr
>
fcppt::unique_ptr<
	Ptr
>
sge::d3d9::device::add_resource(
	fcppt::unique_ptr<
		Ptr
	> _ptr
)
{
	resources_.add(
		*_ptr
	);

	return
		fcppt::move(
			_ptr
		);
}

void
sge::d3d9::device::reinit()
{
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
		!sge::d3d9::devicefuncs::reset(
			device_.get(),
			present_parameters_
		)
	)
		fcppt::time::sleep_any(
			boost::chrono::milliseconds(
				1
			)
		);

	this->reinit();
}
