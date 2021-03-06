/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_TEXTURE_PLANAR_BASIC_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_PLANAR_BASIC_HPP_INCLUDED

#include <sge/image2d/traits/dimension.hpp>
#include <sge/opengl/texture/basic.hpp>
#include <sge/opengl/texture/basic_box.hpp>
#include <sge/opengl/texture/buffer_surface_types.hpp>
#include <sge/opengl/texture/color_surface_types.hpp>
#include <sge/opengl/texture/planar_basic_fwd.hpp>
#include <sge/opengl/texture/planar_types.hpp>
#include <sge/renderer/texture/basic_lockable_box.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

extern
template
class
sge::opengl::texture::basic<
	sge::opengl::texture::planar_types
>;

extern
template
class
sge::opengl::texture::basic_box<
	sge::opengl::texture::planar_types
>;

FCPPT_PP_POP_WARNING

#endif
