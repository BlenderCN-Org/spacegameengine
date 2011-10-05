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


#include "to_opencl_mem_flags.hpp"
#include "../handle_error.hpp"
#include <sge/opencl/memory_object/buffer.hpp>
#include <sge/opencl/context/object.hpp>
#include <fcppt/text.hpp>

sge::opencl::memory_object::buffer::buffer(
	opencl::context::object &_context,
	memory_object::flags_field const &_flags,
	memory_object::byte_size const &_byte_size)
:
	impl_(0)
{
	cl_int error_code;
	impl_ = 
		clCreateBuffer(
			_context.impl(),
			memory_object::to_opencl_mem_flags(
				_flags),
			_byte_size.get(),
			0,
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateBuffer"));
}

cl_mem
sge::opencl::memory_object::buffer::impl()
{
	return impl_;
}

sge::opencl::memory_object::buffer::~buffer()
{
	if(!impl_)
		return;

	cl_int const error_code =
		clReleaseMemObject(
			impl_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseMemObject(buffer)"));
}
