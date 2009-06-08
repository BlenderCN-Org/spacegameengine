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


#ifndef SGE_OPENGL_DEVICE_HPP_INCLUDED
#define SGE_OPENGL_DEVICE_HPP_INCLUDED

#include <sge/config.h>
#include "target_fwd.hpp"
#include "default_target_fwd.hpp"
#include "fbo_target_fwd.hpp"
#include "common.hpp"
#if defined(SGE_WINDOWS_PLATFORM)
#include "windows/state.hpp"
#elif defined(SGE_HAVE_X11)
#include "x11/state.hpp"
#else
#error "Implement me!"
#endif
#include <sge/renderer/adapter_type.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/window/instance_fwd.hpp>
#include <sge/window/dim_type.hpp>
#include <sge/scoped_ptr.hpp>
#include <stack>

namespace sge
{
namespace ogl
{

class device : public renderer::device {
public:
	device(
		renderer::parameters const &param,
		renderer::adapter_type adapter,
		window::instance_ptr wnd);

	void begin_rendering();
	void end_rendering();
	void render(
		renderer::const_vertex_buffer_ptr vb,
		renderer::const_index_buffer_ptr ib,
		renderer::size_type first_vertex,
		renderer::size_type num_vertices,
		renderer::indexed_primitive_type::type ptype,
		renderer::size_type pcount,
		renderer::size_type first_index);
	void render(
		renderer::const_vertex_buffer_ptr vb,
		renderer::size_type first_vertex,
		renderer::size_type num_vertices,
		renderer::nonindexed_primitive_type::type ptype);

	void state(renderer::state::list const &);

	void push_state(renderer::state::list const &);

	void pop_state();

	void texture(
		renderer::const_texture_base_ptr tex,
		renderer::stage_type stage);
	void material(
		renderer::material const &);

	void transform(
		renderer::any_matrix const &);
	void projection(
		renderer::any_matrix const &);
	void texture_transform(
		renderer::any_matrix const &);

	void target(renderer::texture_ptr);

	void viewport(
		renderer::viewport const &);
	
	void viewport_mode(
		renderer::viewport_mode::type);

	void enable_light(
		renderer::light_index index,
		bool enable);

	void light(
		renderer::light_index index,
		renderer::light const &);
	void texture_stage_op(
		renderer::stage_type stage,
		renderer::texture_stage_op::type,
		renderer::texture_stage_op_value::type);
	void texture_stage_arg(
		renderer::stage_type stage,
		renderer::texture_stage_arg::type,
		renderer::texture_stage_arg_value::type);

	renderer::glsl::program_ptr const
	create_glsl_program(
		renderer::glsl::optional_string const &vertex_shader_source,
		renderer::glsl::optional_string const &pixel_shader_source);

	renderer::glsl::program_ptr const
	create_glsl_program(
		renderer::glsl::optional_istream const &vertex_shader_source,
		renderer::glsl::optional_istream const &pixel_shader_source);
	
	void glsl_program(
		renderer::glsl::program_ptr);

	renderer::const_target_ptr const
	target() const;

	renderer::texture_ptr const
	create_texture(
		renderer::dim_type const &,
		image::color::format::type,
		renderer::filter::texture const &,
		renderer::resource_flag_t);

	/*const renderer::volume_texture_ptr
	create_volume_texture(
		renderer::volume_texture::image_view_array const &,
		renderer::filter::texture const &filter,
		renderer::volume_texture::resource_flag_type flags);*/

	renderer::cube_texture_ptr const
	create_cube_texture(
		renderer::size_type border_size,
		image::color::format::type,
		renderer::filter::texture const &,
		renderer::resource_flag_t);

	renderer::vertex_buffer_ptr const
	create_vertex_buffer(
		renderer::vf::dynamic_format const &,
		renderer::size_type size,
		renderer::resource_flag_t flags);

	renderer::index_buffer_ptr const
	create_index_buffer(
		renderer::index::format::type,
		renderer::size_type sz,
		renderer::resource_flag_t flags);

	renderer::caps const caps() const;
	renderer::screen_size const screen_size() const;
	window::instance_ptr const window() const;
private:
	GLenum clear_bit(
		renderer::state::bool_::trampoline_type const &) const;

	void vertex_buffer(
		renderer::const_vertex_buffer_ptr);
	
	fbo_target_ptr const
	create_target();

	void reset_viewport(
		window::dim_type const &);
	void reset_viewport_default();
	void projection_internal();

	renderer::parameters const param;
	window::instance_ptr const wnd;
	renderer::state::list      current_states;
#if defined(SGE_WINDOWS_PLATFORM)
	windows::state state_;
#elif defined(SGE_HAVE_X11)
	x11::state state_;
#endif
	bool fbo_active;
	renderer::any_matrix projection_;
	renderer::viewport_mode::type viewport_mode_;
	renderer::viewport viewport_;
	default_target_ptr default_target_;
	target_ptr target_;

	typedef std::stack<
		renderer::state::list
	> stack_type;

	mutable scoped_ptr<
		renderer::caps
	> caps_;

	stack_type state_levels;
};

}
}

#endif
