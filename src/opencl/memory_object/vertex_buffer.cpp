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


#include "../handle_error.hpp"
#include <sge/opencl/memory_object/vertex_buffer.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/renderer/opengl/buffer/base.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <fcppt/text.hpp>

sge::opencl::memory_object::vertex_buffer::vertex_buffer(
	context::object &_context,
	sge::renderer::vertex_buffer &_vb,
	memory_object::vertex_buffer_lock_mode::type const _lock_mode)
:
	impl_(0)
{
	cl_mem_flags mem_flags;

	switch(_lock_mode)
	{
		case vertex_buffer_lock_mode::read_only:
			mem_flags =
				CL_MEM_READ_ONLY;
		case vertex_buffer_lock_mode::write_only:
			mem_flags =
				CL_MEM_WRITE_ONLY;
		case vertex_buffer_lock_mode::read_write:
			mem_flags =
				CL_MEM_READ_WRITE;
	}

	cl_int error_code;

	impl_ =
		clCreateFromGLBuffer(
			_context.impl(),
			mem_flags,
			dynamic_cast<sge::renderer::opengl::buffer::base &>(
				_vb).id().get(),
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateFromGLBuffer"));
}

cl_mem
sge::opencl::memory_object::vertex_buffer::impl()
{
	return impl_;
}

sge::opencl::memory_object::vertex_buffer::~vertex_buffer()
{
	clReleaseMemObject(
		impl_);
}
