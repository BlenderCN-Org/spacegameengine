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
#include <sge/opencl/kernel/object.hpp>
#include <sge/opencl/memory_object/vertex_buffer.hpp>
#include <sge/opencl/program/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <iostream>

sge::opencl::kernel::object::object(
	program::object &_program,
	kernel::name const &_name)
:
	kernel_(0)
{
	cl_int error_code;

	kernel_ =
		clCreateKernel(
			_program.program_,
			_name.c_str(),
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateKernel"));
}

cl_kernel
sge::opencl::kernel::object::impl()
{
	return kernel_;
}

void
sge::opencl::kernel::object::argument(
	kernel::argument_index const &index,
	memory_object::base &o)
{
	cl_mem mem_ptr = o.impl();

	cl_int const error_code =
		clSetKernelArg(
			kernel_,
			static_cast<cl_uint>(
				index.get()),
			sizeof(
				cl_mem),
			&mem_ptr);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clSetKernelArg"));
}

sge::opencl::kernel::object::~object()
{
	if(!kernel_)
		return;

	cl_int const error_code =
		clReleaseKernel(
			kernel_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseKernel"));
}
