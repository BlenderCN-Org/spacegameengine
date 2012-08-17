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


#ifndef SGE_OPENGL_TEXTURE_VOLUME_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_VOLUME_CONTEXT_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/texture/optional_type.hpp>
#include <sge/opengl/texture/volume_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class volume_context
:
	public sge::opengl::context::system::base
{
	FCPPT_NONCOPYABLE(
		volume_context
	);
public:
	volume_context();

	~volume_context();

	bool
	have_volume_texture() const;

	typedef PFNGLTEXIMAGE3DPROC gl_tex_image_3d;

	typedef PFNGLTEXSUBIMAGE3DPROC gl_tex_sub_image_3d;

	sge::opengl::texture::optional_type const
	volume_texture_type() const;

	gl_tex_image_3d
	tex_image_3d() const;

	gl_tex_sub_image_3d
	tex_sub_image_3d() const;

	sge::opengl::optional_enum const
	max_extent_flag() const;

	typedef void needs_before;

	static sge::opengl::context::system::id const static_id;
private:
	bool const volume_texture_normal_;

	sge::opengl::texture::optional_type const volume_texture_type_;

	gl_tex_image_3d const tex_image_3d_;

	gl_tex_sub_image_3d const tex_sub_image_3d_;

	sge::opengl::optional_enum const max_extent_flag_;
};

}
}
}

#endif
