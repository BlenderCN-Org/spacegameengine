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


#ifndef SGE_OPENGL_TEXTURE_DEPTH_STENCIL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_DEPTH_STENCIL_HPP_INCLUDED

#include <sge/opengl/texture/basic.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/depth_stencil_basic.hpp>
#include <sge/opengl/texture/depth_stencil_fwd.hpp>
#include <sge/opengl/texture/depth_stencil_types.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface_unique_ptr.hpp>
#include <sge/renderer/texture/depth_stencil.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <fcppt/math/dim/object_decl.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class depth_stencil
:
	public sge::opengl::texture::depth_stencil_basic
{
	FCPPT_NONCOPYABLE(
		depth_stencil
	);
public:
	depth_stencil(
		sge::opengl::texture::basic_parameters const &,
		sge::renderer::texture::depth_stencil_parameters const &
	);

	~depth_stencil();

	sge::opengl::texture::depth_stencil::dim const
	size() const;

	sge::renderer::depth_stencil_surface_unique_ptr
	surface() const;
private:
	sge::opengl::texture::depth_stencil::dim const size_;

	sge::renderer::depth_stencil_format::type const format_;
};

}
}
}

#endif
