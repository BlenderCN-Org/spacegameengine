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


#ifndef SGE_OGL_RENDERER_HPP_INCLUDED
#define SGE_OGL_RENDERER_HPP_INCLUDED

#include "../../types.hpp"
#include "../../renderer/renderer.hpp"
#include "../../window.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include "../../win32.hpp"
#elif SGE_LINUX_PLATFORM
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>
#include "../../x_window.hpp"
#include "../../glx.hpp"
#endif

namespace sge
{
namespace ogl
{

class renderer : public sge::renderer {
public:
	renderer(const renderer_parameters& param, unsigned adapter);
	~renderer();

	void begin_rendering();
	void end_rendering();
	void render(vertex_buffer_ptr vb, index_buffer_ptr ib, unsigned first_vertex, unsigned num_vertices, primitive_type ptype, unsigned pcount, unsigned first_index = 0);

	void set_int_state(int_state state, int_type value);
	void set_float_state(float_state state, float_type value);
	void set_bool_state(bool_state state, bool_type value);
	void set_texture_stage_op(stage_type stage, stage_op type, stage_op_value value);
	void set_texture_stage_arg(stage_type stage, stage_arg type, stage_arg_value value);
	void set_filter_state(stage_type stage, filter_arg type, filter_arg_value arg);
	void set_texture(stage_type stage, texture_base_ptr tex);
	void set_material(const material& mat);
	void set_transformation(const matrix4x4<space_unit>& matrix);
	void projection_perspective(space_unit fov, space_unit near, space_unit far);
	void projection_orthogonal();
	void set_render_target(render_target_ptr target);

	texture_ptr create_texture(texture::const_pointer data, texture::size_type width, texture::size_type height, unsigned mip_levels, resource_flag_t flags);
	volume_texture_ptr create_volume_texture(volume_texture::const_pointer data, volume_texture::size_type width, volume_texture::size_type height, volume_texture::size_type depth, resource_flag_t flags);
	cube_texture_ptr create_cube_texture(const cube_side_src_array* data, cube_texture::size_type size, resource_flag_t flags = RF_Default);
	vertex_buffer_ptr create_vertex_buffer(const sge::vertex_format& format, vertex_buffer::size_type size, resource_flag_t flags, vertex_buffer::const_pointer data);
	index_buffer_ptr create_index_buffer(index_buffer::size_type size, resource_flag_t flags, index_buffer::const_pointer data);
	render_target_ptr create_render_target(render_target::size_type width, render_target::size_type height);

	const renderer_caps& caps() const;
	unsigned screen_width() const;
	unsigned screen_height() const;
	window_ptr get_window() const;
private:
	renderer_parameters param;
	void set_vertex_buffer(sge::vertex_buffer_ptr vb);
	void set_index_buffer(sge::index_buffer_ptr ib);
	bool clear_zbuffer, clear_stencil, clear_back_buffer;
	renderer_caps _caps;
#ifdef SGE_WINDOWS_PLATFORM
	win_hdc    hdc;
	win_hglrc  hglrc;
	window_ptr wnd;
#elif SGE_LINUX_PLATFORM
	x_display dsp;
	x_resource<XVisualInfo*> vi;
	glx_context ct;
	shared_ptr<x_colormap> cm;
	x_window_ptr wnd;
	glx_current_guard cg;
	x_resource<XF86VidModeModeInfo**> modes;
	shared_ptr<xf86_resolution_guard> resolution_guard;
#endif
};

}
}

#endif
