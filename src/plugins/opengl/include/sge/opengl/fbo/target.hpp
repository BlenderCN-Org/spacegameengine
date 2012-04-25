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


#ifndef SGE_OPENGL_FBO_TARGET_HPP_INCLUDED
#define SGE_OPENGL_FBO_TARGET_HPP_INCLUDED

#include <sge/opengl/basic_target.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/fbo/attachment_fwd.hpp>
#include <sge/opengl/fbo/attachment_unique_ptr.hpp>
#include <sge/opengl/fbo/context_fwd.hpp>
#include <sge/opengl/fbo/object.hpp>
#include <sge/opengl/fbo/render_buffer_fwd.hpp>
#include <sge/opengl/fbo/target_fwd.hpp>
#include <sge/opengl/texture/surface_base_ptr.hpp>
#include <sge/renderer/color_surface_shared_ptr.hpp>
#include <sge/renderer/depth_stencil_surface_shared_ptr.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/math/vector/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace fbo
{

class target
:
	public sge::opengl::basic_target<
		sge::renderer::target::offscreen
	>
{
	FCPPT_NONCOPYABLE(
		target
	);
public:
	typedef sge::opengl::basic_target<
		sge::renderer::target::offscreen
	> base;

	explicit
	target(
		sge::opengl::context::object &
	);

	~target();
private:
	void
	on_bind();

	void
	on_unbind();

	void
	end_rendering();

	void
	color_surface(
		sge::renderer::color_surface_shared_ptr,
		sge::renderer::target::surface_index
	);

	void
	depth_stencil_surface(
		sge::renderer::depth_stencil_surface_shared_ptr
	);

	sge::renderer::optional_dim2 const
	size() const;

	sge::renderer::screen_unit
	height() const;

	sge::opengl::fbo::attachment_unique_ptr
	create_texture_binding(
		sge::opengl::texture::surface_base_ptr,
		GLenum attachment
	);

	sge::opengl::fbo::attachment_unique_ptr
	create_buffer_binding(
		sge::opengl::fbo::render_buffer const &,
		GLenum attachment
	);

	void
	add_dim(
		sge::renderer::dim2 const &
	);

	void
	remove_dim();

	void
	check();

	sge::opengl::fbo::context &context_;

	sge::opengl::fbo::object fbo_;

	typedef boost::ptr_map<
		sge::renderer::target::surface_index,
		sge::opengl::fbo::attachment
	> attachment_map;

	attachment_map color_attachments_;

	typedef fcppt::scoped_ptr<
		sge::opengl::fbo::attachment
	> scoped_attachment;

	scoped_attachment depth_stencil_attachment_;

	renderer::optional_dim2 dim_;
};

}
}
}

#endif
