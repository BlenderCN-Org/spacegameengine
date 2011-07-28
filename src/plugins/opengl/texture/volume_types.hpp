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


#ifndef SGE_OPENGL_TEXTURE_VOLUME_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_VOLUME_TYPES_HPP_INCLUDED

#include "init_function.hpp"
#include "sub_function.hpp"
#include <sge/renderer/texture/volume_fwd.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace opengl
{
namespace texture
{

struct volume_types
{
	typedef sge::renderer::texture::volume base;

	typedef sge::renderer::texture::volume_parameters parameters;

	static
	sge::renderer::size_type
	min_size();

	static
	fcppt::string
	name();

	typedef texture::init_function<
		3
	>::type init_function_type;

	typedef texture::sub_function<
		3
	>::type sub_function_type;

	static
	init_function_type
	init_function();

	static
	sub_function_type
	sub_function();
};

}
}
}

#endif
