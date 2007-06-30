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


#include "../../../types.hpp"
#include "../../../ptr_cast.hpp"
#include "../../../bit.hpp"
#include "../../../renderer/types.hpp"
#include "../renderer.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../vertex_buffer.hpp"
#include "../texture.hpp"
#include "../cube_texture.hpp"
#include "../volume_texture.hpp"
#include "../conversion.hpp"
#include "../default_render_target.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include "../../../windows.hpp"
#include "../../../win32_window.hpp"
#endif
#include "../common.hpp"

// TODO: consistent error checking

#include <iostream> // TODO: remove when stub messages are gone

namespace
{

inline unsigned num_indices(const sge::primitive_type type, const unsigned count)
{
	switch(type) {
	case sge::PT_Triangle:
		return count*3;
	case sge::PT_Line:
		return count*2;
	default:
		throw std::logic_error("num_indices doesn't make any sense for primitves without inidces");
	}
}

}


// TODO: move the Xerror code somewhere more appropriate

#ifdef SGE_LINUX_PLATFORM

int handler(Display* const d, XErrorEvent* const e)
{
	boost::array<char,1024> buf;
	XGetErrorText(d,e->error_code,buf.c_array(),buf.size());
	std::cerr << "X Error: " << buf.data() << '\n';
	return 0;
}
#endif

// TODO: maybe support different adapters?
sge::ogl::renderer::renderer(const renderer_parameters& param, const unsigned adapter, const window_ptr wnd_param)
 : param(param),
   clearflags(0)
#ifdef SGE_LINUX_PLATFORM
   ,
   dsp(new x_display())
#endif
{
	if(adapter > 0)
		std::cerr << "stub: adapter cannot be > 0 for opengl plugin (adapter was " << adapter << ")\n";

	bool windowed = param.windowed;
#ifdef SGE_WINDOWS_PLATFORM
	const unsigned color_depth = bit_depth_bit_count(param.mode.depth);
	if(!windowed)
	{
		DEVMODE settings;
		memset(&settings,0,sizeof(DEVMODE));
		settings.dmSize=sizeof(DEVMODE);
		settings.dmPelsWidth    = param.mode.width();
		settings.dmPelsHeight   = param.mode.height();
		settings.dmBitsPerPel   = color_depth;
		settings.dmDisplayFrequency = param.mode.refresh_rate;
		settings.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT|DM_DISPLAYFREQUENCY;
		if(ChangeDisplaySettings(&settings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			std::cerr << "Cannot change resolution to " << param.mode << "! Reverting to window mode!\n";
			windowed = false;
		}
	}

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // Size Of This Pixel Format Descriptor
			1,                      // Version Number
			PFD_DRAW_TO_WINDOW |    // Format Must Support Window
			PFD_SUPPORT_OPENGL |    // Format Must Support OpenGL
			PFD_DOUBLEBUFFER,       // Must Support Double Buffering
			PFD_TYPE_RGBA,          // Request An RGBA Format
			BYTE(color_depth),      // Select Our Color Depth
			0, 0, 0, 0, 0, 0,       // Color Bits Ignored
			0,                      // No Alpha Buffer
			0,                      // Shift Bit Ignored
			0,                      // No Accumulation Buffer
			0, 0, 0, 0,             // Accumulation Bits Ignored
			16,                     // 16Bit Z-Buffer (Depth Buffer)
			0,                      // Stencil Buffer
			0,                      // No Auxiliary Buffer
			PFD_MAIN_PLANE,         // Main Drawing Layer
			0,                      // Reserved
			0, 0, 0                 // Layer Masks Ignored
	};

	if(!wnd_param)
		wnd.reset(new win32_window(window::window_size(param.mode.width(),param.mode.height()),""));
	else
		wnd = polymorphic_pointer_cast<win32_window>(wnd_param);

	hdc.reset(new gdi_device(wnd->hwnd(), gdi_device::get_tag()));

	const int pixel_format = ChoosePixelFormat(hdc->hdc(), &pfd);
	if(pixel_format == 0)
		throw std::runtime_error("ChoosePixelFormat() failed");
	if(SetPixelFormat(hdc->hdc(), pixel_format, &pfd) == FALSE)
		throw std::runtime_error("SetPixelFormat() failed");

	context.reset(new wgl_context(*hdc));

	current.reset(new wgl_current(*hdc, *context));

#elif SGE_LINUX_PLATFORM
	XSetErrorHandler(handler);
	const int screen = DefaultScreen(dsp->get());

	if(!windowed)
	{
		modes.reset(new xf86_vidmode_array(dsp, screen));
		resolution = modes->switch_to_mode(param.mode);
		if(!resolution)
		{
			std::cerr << "Warning: No resolution matches against " << param.mode << "! Falling back to window mode!\n";
			windowed = true;
		}
	}

	const int attributes[] = {GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 8, GLX_GREEN_SIZE, 8, GLX_BLUE_SIZE, 8, GLX_DEPTH_SIZE, 16, None};
	visual.reset(new glx_visual(dsp, screen, attributes));

	context.reset(new glx_context(dsp, visual->visual_info()));

	colormap.reset(new x_colormap(dsp, visual->visual_info()));

	XSetWindowAttributes swa;
	swa.colormap = colormap->colormap();
	swa.border_pixel = 0;
	swa.background_pixel = 0;
	swa.override_redirect = windowed ? False : True;
	swa.event_mask = StructureNotifyMask;

	if(wnd_param)
		wnd = polymorphic_pointer_cast<x_window>(wnd_param);
	else
		wnd.reset(new x_window(window::window_pos(0,0), window::window_size(param.mode.width(), param.mode.height()), "spacegameengine", dsp, swa, visual->visual_info()));

	if(!windowed)
		XMapWindow(dsp->get(), wnd->get_window());
	else
		XMapRaised(dsp->get(), wnd->get_window());

	current.reset(new glx_current(dsp, *wnd, context));

	XSync(dsp->get(),False);
#endif
	if(glewInit() != GLEW_OK)
		throw std::runtime_error("glewInit() failed");

	set_bool_state(BS_EnableAlphaBlending,true);
	set_bool_state(BS_EnableZBuffer,false);
	set_bool_state(BS_ClearBackBuffer,true);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	// TODO: implement caps
	_caps.adapter_number = adapter;
	_caps.max_tex_size = 512;

	set_render_target();
}

void sge::ogl::renderer::begin_rendering()
{
	glClear(clearflags);
}

sge::index_buffer_ptr sge::ogl::renderer::create_index_buffer(const index_buffer::size_type size,
                                                              const resource_flag_t flags,
                                                              const index_buffer::const_pointer data)
{
	return index_buffer_ptr(new index_buffer(size,flags,data));
}

sge::ogl::fbo_render_target_ptr sge::ogl::renderer::create_render_target(const render_target::size_type width,
                                                                         const render_target::size_type height)
{
	return fbo_render_target_ptr(new fbo_render_target(width,height));
}

sge::texture_ptr sge::ogl::renderer::create_texture(const texture::const_pointer src,
                                                    const texture::size_type width,
                                                    const texture::size_type height,
                                                    const filter_args& filter,
                                                    const resource_flag_t flags)
{
	return texture_ptr(new texture(src, width, height, filter, flags));
}

sge::vertex_buffer_ptr sge::ogl::renderer::create_vertex_buffer(const sge::vertex_format& format,
                                                                const vertex_buffer::size_type size,
                                                                const resource_flag_t flags,
                                                                const vertex_buffer::const_pointer src)
{
	return vertex_buffer_ptr(new vertex_buffer(size,format,flags,src));
}

sge::volume_texture_ptr sge::ogl::renderer::create_volume_texture(const volume_texture::const_pointer src,
                                                                  const volume_texture::size_type width,
                                                                  const volume_texture::size_type height,
                                                                  const volume_texture::size_type depth,
                                                                  const filter_args& filter,
                                                                  const resource_flag_t flags)
{
	return volume_texture_ptr(new volume_texture(src, width, height, depth, filter, flags));
}

sge::cube_texture_ptr sge::ogl::renderer::create_cube_texture(const cube_side_array* const src,
                                                              const cube_texture::size_type sz,
                                                              const filter_args& filter,
                                                              const resource_flag_t flags)
{
	return cube_texture_ptr(new cube_texture(src, sz, filter, flags));
}

void sge::ogl::renderer::end_rendering()
{
#ifdef SGE_WINDOWS_PLATFORM
	wglSwapLayerBuffers(hdc->hdc(), WGL_SWAP_MAIN_PLANE);
#elif SGE_LINUX_PLATFORM
	glXSwapBuffers(dsp->get(), wnd->get_window());
#endif
}

const sge::renderer_caps& sge::ogl::renderer::caps() const
{
	return _caps;
}

sge::window_ptr sge::ogl::renderer::get_window() const
{
	return wnd;
}

sge::screen_size_t sge::ogl::renderer::screen_size() const
{
	return param.mode.size;
}

void sge::ogl::renderer::render(const vertex_buffer_ptr vb,
                                const index_buffer_ptr ib,
                                const sge::vertex_buffer::size_type first_vertex,
                                const sge::vertex_buffer::size_type num_vertices,
                                const primitive_type ptype,
                                const sge::index_buffer::size_type pcount,
                                const sge::index_buffer::size_type first_index)
{
	set_vertex_buffer(vb);
	const GLenum prim_type = convert_cast<GLenum>(ptype);
	switch(ptype) {
	case PT_Line:
	case PT_Triangle:
		set_index_buffer(ib);
		glDrawElements(prim_type,
		               num_indices(ptype, static_cast<unsigned>(pcount)),
		               GL_UNSIGNED_SHORT,
		               vbo_offset(first_index*2));
		break;
	case PT_Point:
	case PT_LineStrip:
	case PT_TriangleStrip:
	case PT_TriangleFan:
	case PT_LineLoop:
		glDrawArrays(prim_type,
		             static_cast<GLsizei>(first_vertex),
		             static_cast<GLint>(num_vertices));
		break;
	}
	if(is_error())
		throw std::runtime_error("opengl error during rendering!");
}

void sge::ogl::renderer::set_bool_state(const bool_state state, const bool_type value)
{
	switch(state) {
	case BS_ClearBackBuffer:
		set_bit(GL_COLOR_BUFFER_BIT, clearflags, value);
		break;
	case BS_ClearZBuffer:
		set_bit(GL_DEPTH_BUFFER_BIT, clearflags, value);
		break;
	case BS_ClearStencil:
		set_bit(GL_STENCIL_BUFFER_BIT, clearflags, value);
		break;
	default:
		const GLenum glstate = convert_cast<GLenum>(state);
		if(value)
			glEnable(glstate);
		else
			glDisable(glstate);
	}
}

void sge::ogl::renderer::set_float_state(const float_state state, const float_type value)
{
	switch(state) {
	case FS_ZBufferClearVal:
		glClearDepth(value);
		break;
	case FS_FogStart:
	case FS_FogEnd:
	case FS_FogDensity:
		glFogf(convert_fog_float_state(state),value);
		break;
	}
}

void sge::ogl::renderer::set_int_state(const int_state state, const int_type value)
{
	switch(state) {
	case IS_ClearColor:
		glClearColor(red_part_rgba_f(value),green_part_rgba_f(value),blue_part_rgba_f(value),alpha_part_rgba_f(value));
		break;
	case IS_StencilClearVal:
		glClearStencil(value);
		break;
	case IS_DepthClearVal:
		glClearDepth(value);
		break;
	case IS_AmbientLightColor:
		{
		const color4 fc = color_to_color4(value);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, reinterpret_cast<const GLfloat*>(&fc));
		}
		break;
	case IS_FogMode:
		glFogi(GL_FOG_MODE, convert_fog_int_value(value));
		break;
	case IS_FogColor:
		const color4 fc = color_to_color4(value);
		glFogfv(GL_FOG_COLOR, reinterpret_cast<const GLfloat*>(&fc));
	}
}

void sge::ogl::renderer::set_material(const material& mat)
{
	const GLenum face = GL_FRONT_AND_BACK;
	glMaterialfv(face, GL_AMBIENT, reinterpret_cast<const GLfloat*>(&mat.ambient));
	glMaterialfv(face, GL_DIFFUSE, reinterpret_cast<const GLfloat*>(&mat.diffuse));
	glMaterialfv(face, GL_SPECULAR, reinterpret_cast<const GLfloat*>(&mat.specular));
	glMaterialfv(face, GL_EMISSION, reinterpret_cast<const GLfloat*>(&mat.emissive));
	glMaterialf(face, GL_SHININESS, mat.power);
}

void sge::ogl::renderer::set_viewport(const viewport& v)
{
	glViewport(v.x, v.y, v.w, v.h);
}

void sge::ogl::renderer::transform(const math::space_matrix& matrix)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(math::transpose(matrix).data());
}

void sge::ogl::renderer::projection(const math::space_matrix& matrix)
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(math::transpose(matrix).data());
}

void sge::ogl::renderer::set_render_target(const texture_ptr target)
{
	if(!target)
	{
		_render_target.reset(new default_render_target(wnd));
		_render_target->bind_me();
		set_viewport(viewport(0,0,wnd->width(),wnd->height()));
		return;
	}

	const shared_ptr<texture> p(dynamic_pointer_cast<texture>(target));
	const fbo_render_target_ptr ntarget = create_render_target(p->width(),p->height());
	_render_target = ntarget;
	ntarget->bind_texture(p);
	set_viewport(viewport(0,0,static_cast<screen_unit>(p->width()),static_cast<screen_unit>(p->height())));
}

sge::render_target_ptr sge::ogl::renderer::get_render_target() const
{
	return _render_target;
}

void sge::ogl::renderer::set_texture(const texture_base_ptr tex, const stage_type stage)
{
	if(!glActiveTextureARB)
		throw std::runtime_error(extension_not_supported_string("ARB_multitexture"));
	if(stage >= GL_MAX_TEXTURE_UNITS_ARB)
	{
		std::cerr << "GL_MAX_TEXTURE_UNITS_ARB is " << GL_MAX_TEXTURE_UNITS_ARB << ". Setting texture stage " << stage << " ignored!\n";
		return;
	}

	glActiveTextureARB(static_cast<GLenum>(GL_TEXTURE0_ARB + stage));
	glDisable(GL_TEXTURE_1D);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_3D);
	if(!tex)
		return;
	texture_base* const b = ptr_cast<texture_base*>(tex.get());
	glEnable(b->type());
	b->bind_me();
}

// TODO: stage engine?

void sge::ogl::renderer::set_texture_stage_arg(const stage_type stage, const stage_arg type, const stage_arg_value value)
{
	std::cerr << "stub: ogl::renderer::set_texture_stage_arg\n";
}

void sge::ogl::renderer::set_texture_stage_op(const stage_type stage, const stage_op type, const stage_op_value value)
{
	std::cerr << "stub: ogl::renderer::set_texture_stage_op\n";
}

void sge::ogl::renderer::set_vertex_buffer(const sge::vertex_buffer_ptr vb)
{
	vertex_buffer* const ovb = ptr_cast<vertex_buffer*>(vb.get());
	ovb->set_format();
}

void sge::ogl::renderer::set_index_buffer(const sge::index_buffer_ptr ib)
{
	index_buffer* const oib = ptr_cast<index_buffer*>(ib.get());
	oib->bind_me();
}
