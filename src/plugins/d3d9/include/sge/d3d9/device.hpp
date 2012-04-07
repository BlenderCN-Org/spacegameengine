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


#ifndef SGE_D3D9_DEVICE_HPP_INCLUDED
#define SGE_D3D9_DEVICE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/onscreen_target_fwd.hpp>
#include <sge/d3d9/resource_manager.hpp>
#include <sge/d3d9/state/device_fwd.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <awl/window/instance_fwd.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace d3d9
{

class device
:
	public sge::renderer::device
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	device(
		IDirect3D9 *,
		renderer::adapter,
		renderer::parameters const &,
		awl::window::instance &
	);

	~device();

	void
	begin_rendering();

	void
	end_rendering();

	void
	clear(
		renderer::clear_flags_field const &
	);

	void
	render_indexed(
		renderer::index_buffer const &,
		renderer::first_vertex,
		renderer::vertex_count,
		renderer::indexed_primitive_type::type,
		renderer::primitive_count,
		renderer::first_index
	);

	void
	render_nonindexed(
		renderer::first_vertex,
		renderer::vertex_count,
		renderer::nonindexed_primitive_type::type
	);

	void
	activate_vertex_buffer(
		renderer::vertex_buffer const &
	);

	void
	deactivate_vertex_buffer(
		renderer::vertex_buffer const &
	);

	void
	vertex_declaration(
		renderer::const_optional_vertex_declaration_ref const &
	);

	void
	state(
		renderer::state::list const &
	);

	void
	push_state(
		renderer::state::list const &
	);

	void
	pop_state();

	void
	material(
		renderer::material const &
	);

	void
	enable_light(
		renderer::light::index,
		bool enable
	);

	void
	light(
		renderer::light::index,
		renderer::light::object const &
	);

	void
	enable_clip_plane(
		renderer::clip_plane_index,
		bool enable
	);

	void
	clip_plane(
		renderer::clip_plane_index,
		renderer::clip_plane const &
	);

	void
	texture_stage_op(
		renderer::texture::stage,
		renderer::texture::stage_op::type,
		renderer::texture::stage_op_value::type
	);

	void
	texture_stage_arg(
		renderer::texture::stage,
		renderer::texture::stage_arg::type,
		renderer::texture::stage_arg_value::type
	);

	void
	texture(
		renderer::texture::const_optional_base_ref const &,
		renderer::texture::stage
	);

	void
	texture_filter(
		renderer::texture::filter::object const &,
		renderer::texture::stage
	);

	void
	texture_address_mode_s(
		renderer::texture::address_mode_s,
		renderer::texture::stage
	);

	void
	texture_address_mode_t(
		renderer::texture::address_mode_t,
		renderer::texture::stage
	);

	void
	texture_address_mode_u(
		renderer::texture::address_mode_u,
		renderer::texture::stage
	);

	void
	transform(
		renderer::matrix_mode::type,
		renderer::matrix4 const &
	);

	void
	target(
		renderer::optional_target_ref const &
	);

	renderer::glsl::program_unique_ptr
	create_glsl_program();

	renderer::glsl::vertex_shader_unique_ptr
	create_glsl_vertex_shader(
		renderer::glsl::string const &
	);

	renderer::glsl::pixel_shader_unique_ptr
	create_glsl_pixel_shader(
		renderer::glsl::string const &
	);

	renderer::glsl::geometry_shader_unique_ptr
	create_glsl_geometry_shader(
		renderer::glsl::string const &
	);

	void
	glsl_program(
		renderer::glsl::const_optional_program_ref const &
	);

	renderer::target_unique_ptr
	create_target();

	renderer::texture::planar_unique_ptr
	create_planar_texture(
		renderer::texture::planar_parameters const &
	);

	renderer::texture::depth_stencil_unique_ptr
	create_depth_stencil_texture(
		renderer::texture::depth_stencil_parameters const &
	);

	renderer::depth_stencil_surface_unique_ptr
	create_depth_stencil_surface(
		renderer::dim2 const &,
		renderer::depth_stencil_format::type
	);

	renderer::texture::volume_unique_ptr
	create_volume_texture(
		renderer::texture::volume_parameters const &
	);

	renderer::texture::cube_unique_ptr
	create_cube_texture(
		renderer::texture::cube_parameters const &
	);

	renderer::vertex_declaration_unique_ptr
	create_vertex_declaration(
		renderer::vf::dynamic::format const &
	);

	renderer::vertex_buffer_unique_ptr
	create_vertex_buffer(
		renderer::vertex_declaration const &,
		renderer::vf::dynamic::part_index,
		renderer::vertex_count,
		renderer::resource_flags_field const &
	);

	renderer::index_buffer_unique_ptr
	create_index_buffer(
		renderer::index::dynamic::format::type,
		renderer::index_count,
		renderer::resource_flags_field const &
	);

	renderer::onscreen_target &
	onscreen_target() const;

	renderer::optional_target_ref const
	target() const;

	renderer::caps::object const &
	caps() const;
private:
	template<
		typename Ptr
	>
	fcppt::unique_ptr<
		Ptr
	>
	add_resource(
		fcppt::unique_ptr<
			Ptr
		>
	);

	void
	init();

	void
	reset();

	void
	reinit();

	void
	release();

	D3DPRESENT_PARAMETERS present_parameters_;

	typedef fcppt::scoped_ptr<
		IDirect3DDevice9,
		fcppt::com_deleter
	> d3d_device_scoped_ptr;

	d3d_device_scoped_ptr const device_;

	typedef fcppt::scoped_ptr<
		renderer::caps::object
	> caps_scoped_ptr;

	caps_scoped_ptr const caps_;

	d3d9::resource_manager resources_;

	typedef fcppt::scoped_ptr<
		d3d9::onscreen_target
	> onscreen_target_scoped_ptr;

	onscreen_target_scoped_ptr onscreen_target_;

	typedef fcppt::scoped_ptr<
		d3d9::state::device
	> device_state_scoped_ptr;

	device_state_scoped_ptr device_state_;
};

}
}

#endif
