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


#include <sge/opengl/draw_arrays.hpp>
#include <sge/opengl/draw_elements.hpp>
#include <sge/opengl/set_vertex_buffer.hpp>
#include <sge/opengl/set_vertex_declaration.hpp>
#include <sge/opengl/target_base.hpp>
#include <sge/opengl/unset_vertex_buffer.hpp>
#include <sge/opengl/clear/set.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/render_context/object.hpp>
#include <sge/opengl/state/core/sampler/set.hpp>
#include <sge/opengl/texture/activate.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/const_optional_vertex_declaration_ref_fwd.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/state/core/blend/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/alpha_test/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/material/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/misc/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/optional_offscreen_ref.hpp>
#include <sge/renderer/texture/const_optional_base_ref_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/opengl/cg/program/activate.hpp>
#include <sge/opengl/cg/program/deactivate.hpp>
#include <sge/opengl/cg/texture/enable.hpp>
#include <sge/opengl/cg/texture/disable.hpp>
#include <sge/renderer/cg/loaded_program_fwd.hpp>
#include <sge/renderer/cg/loaded_texture_fwd.hpp>
#endif


sge::opengl::render_context::object::object(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::context::device::object &_device_context,
	sge::renderer::target::base &_target
)
:
	sge::renderer::context::ffp(),
	system_context_(
		_system_context
	),
	device_context_(
		_device_context
	),
	target_(
		_target
	),
	scoped_target_(
		dynamic_cast<
			sge::opengl::target_base &
		>(
			target_
		)
	),
	scoped_offscreen_target_()
{
}

sge::opengl::render_context::object::~object()
{
}

void
sge::opengl::render_context::object::end_rendering()
{
	scoped_target_.target().end_rendering();
}

sge::renderer::target::base &
sge::opengl::render_context::object::target()
{
	return
		target_;
}

void
sge::opengl::render_context::object::clear(
	sge::renderer::clear::parameters const &_parameters
)
{
	sge::opengl::clear::set(
		_parameters
	);
}

void
sge::opengl::render_context::object::offscreen_target(
	sge::renderer::target::optional_offscreen_ref const &_new_target
)
{
	if(
		_new_target
	)
	{
		FCPPT_ASSERT_PRE(
			!scoped_offscreen_target_
		);

		scoped_target_.target().unbind();

		scoped_offscreen_target_.take(
			fcppt::make_unique_ptr<
				sge::opengl::render_context::scoped_target
			>(
				fcppt::ref(
					dynamic_cast<
						sge::opengl::target_base &
					>(
						*_new_target
					)
				)
			)
		);
	}
	else
	{
		FCPPT_ASSERT_PRE(
			scoped_offscreen_target_
		);

		scoped_offscreen_target_.reset();

		scoped_target_.target().bind();
	}
}

void
sge::opengl::render_context::object::render_indexed(
	sge::renderer::index_buffer const &_index_buffer,
	sge::renderer::first_vertex const _first_vertex,
	sge::renderer::vertex_count const _num_vertices,
	sge::renderer::primitive_type::type const _primitive_type,
	sge::renderer::first_index const _first_index,
	sge::renderer::index_count const _num_indices
)
{
	sge::opengl::draw_elements(
		system_context_,
		_index_buffer,
		_first_vertex,
		_num_vertices,
		_primitive_type,
		_first_index,
		_num_indices
	);
}

void
sge::opengl::render_context::object::render_nonindexed(
	sge::renderer::first_vertex const _first_vertex,
	sge::renderer::vertex_count const _num_vertices,
	sge::renderer::primitive_type::type const _primitive_type
)
{
	sge::opengl::draw_arrays(
		_first_vertex,
		_num_vertices,
		_primitive_type
	);
}

void
sge::opengl::render_context::object::activate_vertex_buffer(
	sge::renderer::vertex_buffer const &_vertex_buffer
)
{
	sge::opengl::set_vertex_buffer(
		device_context_,
		_vertex_buffer
	);
}

void
sge::opengl::render_context::object::deactivate_vertex_buffer(
	sge::renderer::vertex_buffer const &_vertex_buffer
)
{
	sge::opengl::unset_vertex_buffer(
		device_context_,
		_vertex_buffer
	);
}

void
sge::opengl::render_context::object::vertex_declaration(
	sge::renderer::const_optional_vertex_declaration_ref const &_vertex_declaration
)
{
	sge::opengl::set_vertex_declaration(
		device_context_,
		_vertex_declaration
	);
}

void
sge::opengl::render_context::object::texture(
	sge::renderer::texture::const_optional_base_ref const &_texture,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::activate(
		system_context_,
		device_context_,
		_texture,
		_stage
	);
}

void
sge::opengl::render_context::object::blend_state(
	sge::renderer::state::core::blend::const_optional_object_ref const &
)
{
}

void
sge::opengl::render_context::object::depth_stencil_state(
	sge::renderer::state::core::depth_stencil::const_optional_object_ref const &
)
{
}

void
sge::opengl::render_context::object::rasterizer_state(
	sge::renderer::state::core::rasterizer::const_optional_object_ref const &
)
{
}

void
sge::opengl::render_context::object::sampler_state(
	sge::renderer::state::core::sampler::const_object_ref_vector const &_state
)
{
	sge::opengl::state::core::sampler::set(
		_state
	);
}

void
sge::opengl::render_context::object::alpha_test_state(
	sge::renderer::state::ffp::alpha_test::const_optional_object_ref const &
)
{
}

void
sge::opengl::render_context::object::clip_plane_state(
	sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &
)
{
}

void
sge::opengl::render_context::object::lighting_state(
	sge::renderer::state::ffp::lighting::const_optional_object_ref const &
)
{
}

void
sge::opengl::render_context::object::lights_state(
	sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &
)
{
}

void
sge::opengl::render_context::object::material_state(
	sge::renderer::state::ffp::lighting::material::const_optional_object_ref const &
)
{
}

void
sge::opengl::render_context::object::misc_state(
	sge::renderer::state::ffp::misc::const_optional_object_ref const &
)
{
}

void
sge::opengl::render_context::object::sampler_ffp_state(
	sge::renderer::state::ffp::sampler::const_object_ref_vector const &
)
{
}

void
sge::opengl::render_context::object::transform(
	sge::renderer::state::ffp::transform::mode::type,
	sge::renderer::state::ffp::transform::const_optional_object_ref const &
)
{
}

#if defined(SGE_RENDERER_HAVE_CG)
void
sge::opengl::render_context::object::set_cg_program(
	sge::renderer::cg::loaded_program const &_program
)
{
	sge::opengl::cg::program::activate(
		_program
	);
}

void
sge::opengl::render_context::object::unset_cg_program(
	sge::renderer::cg::loaded_program const &_program
)
{
	sge::opengl::cg::program::deactivate(
		_program
	);
}

sge::renderer::texture::stage const
sge::opengl::render_context::object::set_cg_texture(
	sge::renderer::cg::loaded_texture const &_texture
)
{
	return
		sge::opengl::cg::texture::enable(
			_texture
		);
}

void
sge::opengl::render_context::object::unset_cg_texture(
	sge::renderer::cg::loaded_texture const &_texture
)
{
	sge::opengl::cg::texture::disable(
		_texture
	);
}
#endif
