/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_FBO_DEPTH_STENCIL_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_FBO_DEPTH_STENCIL_SURFACE_HPP_INCLUDED

#include "depth_stencil_surface_fwd.hpp"
#include "render_buffer.hpp"
#include "context_fwd.hpp"
#include "../common.hpp"
#include <sge/renderer/depth_stencil_surface.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace fbo
{

class depth_stencil_surface
:
	public sge::renderer::depth_stencil_surface
{
	FCPPT_NONCOPYABLE(
		depth_stencil_surface
	)
public:
	explicit depth_stencil_surface(
		fbo::context const &,
		GLenum internal_format,
		dim_type const &
	);

	~depth_stencil_surface();

	fbo::render_buffer const &
	render_buffer() const;
private:
	dim_type const
	dim() const;

	fbo::render_buffer const render_buffer_;

	dim_type const dim_;
};	

}
}
}

#endif
