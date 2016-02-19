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


#ifndef SGE_OPENCL_KERNEL_NUMERIC_TYPE_HPP_INCLUDED
#define SGE_OPENCL_KERNEL_NUMERIC_TYPE_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <fcppt/variant/variadic.hpp>


namespace sge
{
namespace opencl
{
namespace kernel
{

typedef
fcppt::variant::variadic<
	cl_char,
	cl_uchar,
	cl_short,
	cl_ushort,
	cl_int,
	cl_uint,
	cl_long,
	cl_ulong,
	cl_half,
	cl_float,
	cl_double
>
numeric_type;

}
}
}

#endif
