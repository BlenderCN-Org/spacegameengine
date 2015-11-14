/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/mipmap/context.hpp>
#include <sge/opengl/texture/mipmap/generate.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::texture::mipmap::generate(
	sge::opengl::texture::binding const &,
	sge::opengl::context::object &_context,
	sge::opengl::texture::type const _type
)
{
	fcppt::optional_to_exception(
		sge::opengl::context::use<
			sge::opengl::texture::mipmap::context
		>(
			_context,
			_context.info()
		).generate_mipmap(),
		[]{
			return
				sge::renderer::unsupported(
					FCPPT_TEXT("GenerateMipmaps"),
					FCPPT_TEXT("GL_VERSION_3_0"),
					FCPPT_TEXT("glGenerateMipmapsEXT")
				);
		}
	)(
		_type.get()
	);
}
