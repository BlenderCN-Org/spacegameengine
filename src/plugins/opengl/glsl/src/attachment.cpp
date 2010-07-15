/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../attachment.hpp"
#include "../programfuncs/attach_shader.hpp"
#include "../programfuncs/detach_shader.hpp"
#include "../normal/environment.hpp"
//#include "../arb/environment.hpp"
#include <fcppt/dynamic_pointer_cast.hpp>

template<
	typename Environment
>
sge::opengl::glsl::attachment<Native>::attachment(
	typename Environment::program_context &_context,
	sge::renderer::glsl::shader_ptr const _shader,
	handle const _handle
)
:
	context_(
		_context
	),
	shader_(
		fcppt::dynamic_pointer_cast<
			shader_type
		>(
			_shader
		)
	),
	handle_(_handle)
{
	programfuncs::attach_shader<
		Environment
	>(
		_context,
		_handle,
		shader_->id()
	);
}

template<
	typename Environment
>
sge::opengl::glsl::attachment<Environment>::~attachment()
{
	programfuncs::detach_shader<
		Environment
	>(
		_context,
		handle_,
		shader_->id()
	);
}

template class sge::opengl::glsl::attachment<
	sge::opengl::glsl::normal::environment
>;

#if 0
template class sge::opengl::glsl::attachment<
	sge::opengl::glsl::arb::environment
>;
#endif
