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


#ifndef SGE_OPENGL_TEXTURE_MIPMAP_PARAMETERS_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_MIPMAP_PARAMETERS_HPP_INCLUDED

#include "parameters_fwd.hpp"
#include "../init_function.hpp"
#include "../scoped_work_bind_fwd.hpp"
#include "../type.hpp"
#include "../../context/object_fwd.hpp"
#include <sge/renderer/basic_dim.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace opengl
{
namespace texture
{
namespace mipmap
{

template<
	fcppt::math::size_type Dim
>
class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	typedef typename renderer::basic_dim<
		Dim
	>::type dim;

	typedef typename texture::init_function<
		Dim
	>::type init_function_type;

	parameters(
		texture::scoped_work_bind const &,
		opengl::context::object &,
		texture::type,
		dim const &,
		init_function_type const &
	);
private:
	texture::scoped_work_bind const &scoped_work_;

	opengl::context::object &context_;

	texture::type const type_;

	dim const size_;

	init_function_type const init_function_;
};

}
}
}
}

#endif
