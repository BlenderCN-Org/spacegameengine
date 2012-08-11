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
#include <sge/d3d9/resource_manager.hpp>
#include <sge/d3d9/swapchain/d3d_scoped_ptr.hpp>
#include <sge/d3d9/target/onscreen_fwd.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface_unique_ptr.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/index_buffer_unique_ptr.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/vertex_buffer_unique_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_unique_ptr.hpp>
#include <sge/renderer/caps/device_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/renderer/context/object_unique_ptr.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/occlusion_query/object_unique_ptr.hpp>
#include <sge/renderer/parameters/object_fwd.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/renderer/target/onscreen_fwd.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_unique_ptr.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_unique_ptr.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <sge/renderer/vf/dynamic/format_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/unique_ptr_fwd.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#endif


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
		sge::renderer::adapter,
		sge::renderer::parameters::object const &,
		awl::window::object &,
		sge::renderer::caps::device const &
	);

	~device();

	sge::renderer::context::object_unique_ptr
	begin_rendering(
		sge::renderer::target::base &
	);

	void
	end_rendering(
		sge::renderer::context::object &
	);

	sge::renderer::target::offscreen_unique_ptr
	create_target();

	sge::renderer::texture::planar_unique_ptr
	create_planar_texture(
		sge::renderer::texture::planar_parameters const &
	);

	sge::renderer::texture::depth_stencil_unique_ptr
	create_depth_stencil_texture(
		sge::renderer::texture::depth_stencil_parameters const &
	);

	sge::renderer::depth_stencil_surface_unique_ptr
	create_depth_stencil_surface(
		sge::renderer::dim2 const &,
		sge::renderer::depth_stencil_format::type
	);

	sge::renderer::texture::volume_unique_ptr
	create_volume_texture(
		sge::renderer::texture::volume_parameters const &
	);

	sge::renderer::texture::cube_unique_ptr
	create_cube_texture(
		sge::renderer::texture::cube_parameters const &
	);

	sge::renderer::vertex_declaration_unique_ptr
	create_vertex_declaration(
		sge::renderer::vf::dynamic::format const &
	);

	sge::renderer::vertex_buffer_unique_ptr
	create_vertex_buffer(
		sge::renderer::vertex_declaration const &,
		sge::renderer::vf::dynamic::part_index,
		sge::renderer::vertex_count,
		sge::renderer::resource_flags_field const &
	);

	sge::renderer::index_buffer_unique_ptr
	create_index_buffer(
		sge::renderer::index::dynamic::format::type,
		sge::renderer::index_count,
		sge::renderer::resource_flags_field const &
	);

	sge::renderer::occlusion_query::object_unique_ptr
	create_occlusion_query();

#if defined(SGE_RENDERER_HAVE_CG)
	sge::cg::profile::object const
	create_cg_profile(
		sge::cg::profile::shader_type::type
	);

	sge::cg::program::compile_options const
	cg_compile_options(
		sge::cg::context::object const &,
		sge::cg::profile::object const &
	);

	sge::renderer::cg::loaded_program_unique_ptr
	load_cg_program(
		sge::cg::program::object &
	);

	sge::renderer::cg::loaded_texture_unique_ptr
	load_cg_texture(
		sge::cg::parameter::object const &,
		sge::renderer::texture::base &
	);

	sge::cg::program::source const
	transform_cg_vertex_program(
		sge::renderer::vertex_declaration const &,
		sge::cg::program::source const &
	);
#endif

	sge::renderer::target::onscreen &
	onscreen_target() const;

	sge::renderer::caps::device const &
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
	reset();

	void
	reinit();

	void
	release();

	sge::renderer::pixel_format::srgb::type const srgb_;

	sge::renderer::caps::device const &caps_;

	D3DPRESENT_PARAMETERS present_parameters_;

	typedef fcppt::scoped_ptr<
		IDirect3DDevice9,
		fcppt::com_deleter
	> d3d_device_scoped_ptr;

	d3d_device_scoped_ptr const device_;

	sge::d3d9::resource_manager resources_;

	sge::d3d9::swapchain::d3d_scoped_ptr const swap_chain_;

	typedef fcppt::scoped_ptr<
		sge::d3d9::target::onscreen
	> onscreen_target_scoped_ptr;

	onscreen_target_scoped_ptr const onscreen_target_;
};

}
}

#endif
